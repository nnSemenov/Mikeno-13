
#include "volFieldsFwd.H"
#include "porousMediaFluid.H"

namespace Foam {
namespace solvers {

    defineTypeNameAndDebug(porousMediaFluid, 0);
    addToRunTimeSelectionTable(solver, porousMediaFluid, fvMesh);
}
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
    )
{
    auto thermo=solidThermo::New(mesh, "porous");
    auto transport=solidThermophysicalTransportModel::New(thermo());
    // should be either h or e
    const word fluid_phase_thermo_name = this->thermo().he().name();
    // Solid and fluid should have same energy type
    thermo->validate("solid", fluid_phase_thermo_name);
    porousPhases.emplace_back(
        porousPhase {
            .alpha = volScalarField (
                IOobject (
                    "alpha.porous",
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
    porousPhases[0].alpha.writeOpt()=IOobject::AUTO_WRITE;

    this->updatePorosity();
    this->U_physical=this->U();
    this->U_physical /= this->porosity_;
}

Foam::solvers::porousMediaFluid::~porousMediaFluid() {}

void Foam::solvers::porousMediaFluid::updatePorosity() {
    // fill with 1
    porosity_.primitiveFieldRef()=1;
    porosity_.boundaryFieldRef()=1;
    for(auto & porPhase: porousPhases) {
        porosity_-=porPhase.alpha;
    }
}


void Foam::solvers::porousMediaFluid::momentumPredictor() {
    isothermalFluid::momentumPredictor();
    this->U_physical=this->U();
    this->U_physical /= this->porosity_;
}
