#include "porousPhaseInfo.H"
#include "IOdictionary.H"
// #include <boost/graph/detail/adjacency_list.hpp>
// #include <boost/graph/graph_mutability_traits.hpp>
// #include <boost/graph/graph_traits.hpp>
// #include <boost/graph/properties.hpp>
// #include <boost/graph/undirected_graph.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/named_function_params.hpp>
#include <cstdlib>
#include <vector>

#include "cubicEOS.H"

using Foam::word, Foam::List;

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
            boost::add_edge(getPhaseVertex(phaseA),getPhaseVertex(phaseB),
                phaseTransferProperty{.heatTransfer=heatTransfer},
                g);
        }
    }
    Info<<"Added "<<boost::num_edges(this->heatTransferGraph_)<<" heat transfer pathes"<<endl;

    auto eq_phase_list = this->thermalEquilibriumPhases();
    Info<<"Thermal equilbrium phases: ";
    for(auto & phase_list: eq_phase_list) {
        Info<<"\n  (";
        for(auto & phase: phase_list) {
            Info<<phase<<" ";
        }
        Info<<"\b)";
    }
    Info<<endl;
}

class DFSVisitor: public boost::default_dfs_visitor {
    public:
    std::vector<word> * phase_list;
    std::vector<Foam::porousPhaseInfo::heatTransferGraph_type::vertex_descriptor> * vert_list;

    template<typename vertex,typename Graph>
     void discover_vertex(vertex v, Graph g) const {
        word phaseName = g[v];
        phase_list->emplace_back(phaseName);
        vert_list->emplace_back(v);
     }
};

std::vector<std::vector<word>> Foam::porousPhaseInfo::thermalEquilibriumPhases() const {
    heatTransferGraph_type graph{this->heatTransferGraph_};

    // Remove all non-thermal-equilibrium heat transfer links
    auto pred = [&](auto edge)->bool {
        const heatTransfer&ht = graph[edge].heatTransfer;
        if(std::get_if<equilibriumHeatTransfer>(&ht)==nullptr) {
            return true;
        }
        return false;
    };
    boost::remove_edge_if(pred, graph);
    
    std::vector<std::vector<word>> ret;
    while (true) {
        if(boost::num_vertices(graph)<=0) {
            break;
        }
        std::vector<word> phases;
        std::vector<heatTransferGraph_type::vertex_descriptor> verts;
        DFSVisitor vis;
        vis.phase_list=&phases;
        vis.vert_list=&verts;
        boost::depth_first_search(graph, boost::visitor(vis));
        // Info<<"Found "<<phases.size()<<" isothermal phase(s) from "<<boost::num_vertices(graph)<<" phase(s)"<<endl;

        for(auto it=verts.rbegin();it not_eq verts.rend();++it) {
            boost::remove_vertex(*it, graph);
        }
        ret.emplace_back(std::move(phases));
    }

    return ret;
}