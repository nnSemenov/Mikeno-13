
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
            IOobject::NO_READ, 
            IOobject::AUTO_WRITE
        ),
        mesh
    )
{
    auto thermo=solidThermo::New(mesh, "porous");
    auto transport=solidThermophysicalTransportModel::New(thermo());
    thermo->validate("solid", "h", "e");
    porousPhases.emplace_back(
        porousPhase {
            .alpha=volScalarField (
                IOobject (
                    "alpha.porous",
                    runTime.name(),
                    mesh,
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                mesh
            ),
            .thermo=std::move(thermo),
            .thermophysicalTransport=std::move(transport)
        }
    );

    this->updatePorosity();
    // this->U_physical=this->U();
    // this->U_physical /= this->porosity_;
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