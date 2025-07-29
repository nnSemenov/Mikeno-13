#include "porousMediaFluid.H"
#include "fvcDdt.H"
#include "fvmDiv.H"

Foam::tmp<Foam::volScalarField::Internal> 
Foam::solvers::porousMediaFluid::TEqnNonIdealityPressureTerm(const volScalarField& dhedp_T) const {
    auto left = rho_ * U_ & fvc::grad(p());
    return dhedp_T.internalField() * (
        left->internalField()
        + rho_.internalField() * dpdt
    );
}

void Foam::solvers::porousMediaFluid::thermophysicalPredictor() {
    auto & thermo=this->thermoPtr_();
    volScalarField & T=thermo.T();
    const volScalarField& he = thermo.he();
    const bool internalEnergy = he.name() == "e";
    const auto Cpv=thermo.Cpv();
    const auto kappaEff = this->thermophysicalTransport->kappaEff();
    const surfaceScalarField phiCpv =(fvc::interpolate(Cpv) * phi_)();

    const volScalarField & dhedp_T = thermo.dhedp_T();
    
    fvScalarMatrix TEqn (
        rho_ * Cpv* fvm::ddt(T) 
        + fvm::div(phiCpv, T) 
            - fvm::SuSp(fvc::div(phiCpv), T)
        + TEqnNonIdealityPressureTerm(dhedp_T)

        + fvc::ddt(rho_, K) + fvc::div(phi_, K)
        - fvm::laplacian(kappaEff, T)
        + pressureWork
          (
            internalEnergy
            ? fvc::div(phi_, p_()/rho_)()
            : -dpdt
          )
        ==
            (
                buoyancy.valid()
            ? fvModels().source(rho_*Cpv, T) + rho_*(U_ & buoyancy->g)
            : fvModels().source(rho_*Cpv, T)
            )
    );

    TEqn.relax();

    fvConstraints().constrain(TEqn);

    TEqn.solve();

    fvConstraints().constrain(T);

    thermo.he() = thermo.he(this->p_(), T);
    this->thermoPtr_().correct();
}