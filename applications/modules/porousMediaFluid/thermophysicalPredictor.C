#include "porousMediaFluid.H"
#include "fvcDdt.H"
#include "fvmDiv.H"

void Foam::solvers::porousMediaFluid::thermophysicalPredictor() {
    auto & thermo=this->thermoPtr_();
    volScalarField & T=thermo.T();
    const auto Cpv=thermo.Cpv();
    const auto kappaEff = this->thermophysicalTransport->kappaEff();
    const surfaceScalarField phiCpv =(fvc::interpolate(Cpv) * phi_)();
    
    fvScalarMatrix TEqn (
        rho_ * Cpv* fvm::ddt(T) 
        + fvm::div(phiCpv, T) 
            - fvm::SuSp(fvc::div(phiCpv), T)
        #warning Add dhdp_T here
        + fvc::ddt(rho_, K) + fvc::div(phi_, K)
        - dpdt
        - fvm::laplacian(kappaEff, T)
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