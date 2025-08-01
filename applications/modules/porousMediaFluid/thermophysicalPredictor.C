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
    const surfaceScalarField phiCpv =(fvc::interpolate(Cpv) * phi_)();

    const volScalarField & dhedp_T = thermo.dhedp_T();

    const volScalarField & alphaF = this->porosity_;


    volScalarField kappaEff = (this->thermophysicalTransport->kappaEff() * alphaF)();
    volScalarField rhoCpEff = (alphaF* rho_ * Cpv)();
    for(auto & pair: this->porousPhases.porousPhases()) {
        const auto & alphaP=pair.second.alpha;
        auto & thermoP=pair.second.thermo;
        const volScalarField& rhoP=thermoP->rho();
        const volScalarField& CpvP=thermoP->Cpv();
        rhoCpEff+=alphaP*rhoP*CpvP;
        kappaEff+=alphaP*thermoP->kappa();
    }
    // Thermal equilbrium 
    fvScalarMatrix TEqn (

        rhoCpEff* fvm::ddt(T) 
        + alphaF*(fvm::div(phiCpv, T) 
            - fvm::SuSp(fvc::div(phiCpv), T))
        + alphaF*TEqnNonIdealityPressureTerm(dhedp_T)

        + alphaF*(fvc::ddt(rho_, K) + fvc::div(phi_, K)) // Fluid kinetic
        - fvm::laplacian(kappaEff, T)
        + alphaF*pressureWork
          (
            internalEnergy
            ? fvc::div(phi_, p_()/rho_)()
            : -dpdt
          )
        ==
        (
            buoyancy.valid()
        ? fvModels().source(rhoCpEff, T) + alphaF*rho_*(U_ & buoyancy->g)
        : fvModels().source(rhoCpEff, T)
        )
    );

    // Fluid only
    // fvScalarMatrix TEqn (
    //     rho_ * Cpv* fvm::ddt(T) 
    //     + fvm::div(phiCpv, T) 
    //         - fvm::SuSp(fvc::div(phiCpv), T)
    //     + TEqnNonIdealityPressureTerm(dhedp_T)

    //     + fvc::ddt(rho_, K) + fvc::div(phi_, K)
    //     - fvm::laplacian(kappaEff, T)
    //     + pressureWork
    //       (
    //         internalEnergy
    //         ? fvc::div(phi_, p_()/rho_)()
    //         : -dpdt
    //       )
    //     ==
    //         (
    //             buoyancy.valid()
    //         ? fvModels().source(rho_*Cpv, T) + rho_*(U_ & buoyancy->g)
    //         : fvModels().source(rho_*Cpv, T)
    //         )
    // );

    TEqn.relax();

    fvConstraints().constrain(TEqn);

    TEqn.solve();

    fvConstraints().constrain(T);
    // Update energy
    thermo.he() = thermo.he(this->p_(), T);
    // Update other properties
    this->thermoPtr_().correct();

    for(auto & pair: this->porousPhases.porousPhases()) {
        auto & thermoP=pair.second.thermo;
        thermoP->T()=T;
        thermoP->he() = thermoP->he(this->p_(), T);
        thermoP->correct();
    }

}