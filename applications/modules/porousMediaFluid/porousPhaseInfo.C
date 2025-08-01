#include "porousPhaseInfo.H"
#include "IOdictionary.H"
#include <boost/graph/detail/adjacency_list.hpp>
#include <boost/graph/graph_mutability_traits.hpp>
#include <boost/graph/undirected_graph.hpp>
#include <cstdlib>

#include "cubicEOS.H"

const Foam::word Foam::porousPhaseInfo::FLUID_PHASE_NAME{"fluid"};

Foam::heatTransfer Foam::parse_heatTransfer(const Foam::dictionary& dict) {
    using namespace Foam;
    const word type = dict.lookup<word>("type");
    if(type=="equilibrium") {
        return equilibriumHeatTransfer {};
    }

    if(type=="nonEquilibrium") {
        const auto alpha = dict.lookup<dimensionedScalar>("heatTransferCoeff");
        const auto area = dict.lookup<dimensionedScalar>("specificSurfaceArea");
        // Info<<"Dimension of heat transfer coeff: "<<alpha.dimensions()<<"\n, specific surface area: "<<area.dimensions()<<endl;
        const dimensionSet dimHeatTransferCoeff(1,0,-3,-1,0);
        const dimensionSet dimSpecificSurfaceArea(0,-1,0,0,0);
        bool ok=true;
        if(not (alpha.dimensions() == dimHeatTransferCoeff)) {
            Info<<"Wrong dimension for heatTransferCoeff, must be "<<dimHeatTransferCoeff<<", found "<<alpha.dimensions()<<endl;
            ok=false;
        }
        if(not (area.dimensions() == dimSpecificSurfaceArea)) {
            Info<<"Wrong dimension for specificSurfaceArea, must be "<<dimSpecificSurfaceArea<<", found "<<area.dimensions()<<endl;
            ok=false;
        }
        if(not ok) {
            std::abort();
        }

        return nonEquilibriumHeatTransfer {
            .heatTransferCoefficient=alpha,
            .effectiveSpecificSurfaceArea=area
        };
    }

    Info<<"Unknown heat transfer type "<<type<<endl;
    std::abort();
    return {};
}

Foam::porousPhaseInfo::porousPhaseInfo(fvMesh&mesh, const Time& runTime): heatTransferGraph_(0) {
    IOdictionary porousPhaseDict (
        IOobject (
            "phaseProperties",
            runTime.constant(),
            mesh,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        )
    );
    wordList phaseNameList(porousPhaseDict.lookup<wordList>("porousPhases"));

    for(const word& phaseName: phaseNameList) {
        if(phaseName==FLUID_PHASE_NAME) {
            FatalErrorInFunction<<"Invalid phase name for porous media: "<<phaseName<<endl;
            ::Foam::abort(::Foam::FatalError);
        }

        if(porousPhases_.find(phaseName) not_eq porousPhases_.end()) {
            FatalErrorInFunction<<"Porous phase name "<<phaseName<<" is already defined."<<endl;
            ::Foam::abort(::Foam::FatalError);
        }
        auto thermo=solidThermo::New(mesh, phaseName);
        auto transport=solidThermophysicalTransportModel::New(thermo());
        thermo->validate("solid", "h", "e");
        auto it = porousPhases_.emplace(phaseName, 
            porousPhase {
                .alpha = volScalarField (
                    IOobject (
                        "alpha."+phaseName,
                        runTime.name(),
                        mesh,
                        IOobject::MUST_READ,
                        IOobject::AUTO_WRITE,
                        true // registered
                    ),
                    mesh
                ),
                .thermo=std::move(thermo),
                .thermophysicalTransport=std::move(transport)
            }
        );
        // force solver to write alpha (why AUTO_WRITE above doesn't work ?!)
        it.first->second.alpha.writeOpt()=IOobject::AUTO_WRITE;
    }

    Info<<"Create "<<phaseNameList.size()<<" porous phases: "<<phaseNameList<<endl;

    for(auto & phase: this->porousPhases_) {
        auto & g=this->heatTransferGraph_;
        auto vert = boost::add_vertex(phase.first, g);
        phase.second.vertex=vert;
    }
    this->fluid_vertex=boost::add_vertex(FLUID_PHASE_NAME, this->heatTransferGraph_);

    auto getPhaseVertex = [this](const word&phaseName) {
        if(phaseName==FLUID_PHASE_NAME) {
            return this->fluid_vertex;
        }
        return this->porousPhases_.at(phaseName).vertex;
    };
    {
        const auto & heatTransferDict = porousPhaseDict.subDict("heatTransfer");
        const auto keys = heatTransferDict.keys(true);
        for(const word& key: keys) {
            word phaseA, phaseB;
            const word error=parseBinarySpeciePair(key, phaseA, phaseB);
            if(not error.empty()) {
                FatalErrorInFunction<<"Invalid phase heat transfer table: "<<error<<endl;
                ::Foam::abort(::Foam::FatalError);
            }
            Info<<"Creating heat transfer between "<<phaseA<<" and "<<phaseB<<endl;
            for(const auto & phaseName: {phaseA, phaseB}) {
                if(not isValidPhase(phaseName)) {
                    FatalErrorInFunction<<"Invalid phase name \""<<phaseName<<"\", no such phase"<<endl;
                    ::Foam::abort(::Foam::FatalError);
                }
            }

            auto heatTransfer = parse_heatTransfer(heatTransferDict.subDict(key));

            auto & g=this->heatTransferGraph_;
            boost::add_edge(getPhaseVertex(phaseA),getPhaseVertex(phaseB),heatTransfer,g);
        }
    }
    Info<<"Added "<<boost::num_edges(this->heatTransferGraph_)<<" heat transfer pathes"<<endl;
}