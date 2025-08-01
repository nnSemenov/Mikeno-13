
#include "volFieldsFwd.H"
#include "porousMediaFluid.H"

#include <cstdlib>

namespace Foam {
namespace solvers {

    defineTypeNameAndDebug(porousMediaFluid, 0);
    addToRunTimeSelectionTable(solver, porousMediaFluid, fvMesh);
}
}

Foam::porousPhaseInfo::porousPhaseInfo(fvMesh&mesh, const Time& runTime) {
    IOdictionary porousPhaseDict (
        IOobject (
            "phaseProperties",
            runTime.constant(),
            mesh,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        )
    );
    Info<<"keys: "<<porousPhaseDict.keys()<<endl;
    wordList phaseNameList(porousPhaseDict.lookup<wordList>("porousPhases"));

    for(const word& phaseName: phaseNameList) {
        if(porousPhases_.find(phaseName) not_eq porousPhases_.end()) {
            Info<<"Porous phase name "<<phaseName<<" is already defined."<<endl;
            std::exit(1);
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
}

Foam::solvers::porousMediaFluid::porousMediaFluid(fvMesh&mesh) :
    fluid(mesh),
    U_physical(
        IOobject(
            "U_physical", 
            runTime.name(), 
            mesh,
            IOobject::READ_IF_PRESENT, 
            IOobject::AUTO_WRITE
        ),
        this->U_
    ),
    porosity_(
        IOobject(
            "porosity",
            runTime.name(),
            mesh,
            IOobject::READ_IF_PRESENT, 
            IOobject::AUTO_WRITE
        ),
        mesh,
        scalar{1}
    ),
    porousPhases(mesh, runTime)
{
    const word fluid_phase_thermo_name = this->thermo().he().name();
    // Solid and fluid should have same energy type
    for(auto & porPhase: this->porousPhases.porousPhases()) {
        porPhase.second.thermo->validate("solid", fluid_phase_thermo_name);
    }

    this->updatePorosity();
    this->U_physical=this->U();
    this->U_physical /= this->porosity_;
}

Foam::solvers::porousMediaFluid::~porousMediaFluid() {}

void Foam::solvers::porousMediaFluid::updatePorosity() {
    // fill with 1
    porosity_.primitiveFieldRef()=1;
    porosity_.boundaryFieldRef()=1;
    for(auto & porPhase: porousPhases.porousPhases()) {
        porosity_-=porPhase.second.alpha;
    }
}


void Foam::solvers::porousMediaFluid::momentumPredictor() {
    isothermalFluid::momentumPredictor();
    this->U_physical=this->U();
    this->U_physical /= this->porosity_;
}
