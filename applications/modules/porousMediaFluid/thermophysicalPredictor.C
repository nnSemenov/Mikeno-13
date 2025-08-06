#include "porousMediaFluid.H"
#include "fvcDdt.H"
#include "fvmDiv.H"
#include <optional>

using namespace Foam;

tmp<volScalarField::Internal> 
solvers::porousMediaFluid::TEqnNonIdealityPressureTerm(const volScalarField& dhedp_T) const {
    auto left = rho_ * U_ & fvc::grad(p());
    return dhedp_T.internalField() * (
        left->internalField()
        + rho_.internalField() * dpdt
    );
}
tmp<fvScalarMatrix> solvers::porousMediaFluid::TEqnCore(porousPhaseInfo::heatTransferInfoNode& node) {
    auto getAlpha = [&](const word& phaseName) ->const volScalarField& {
        if(phaseName==porousPhaseInfo::FLUID_PHASE_NAME) {
            return this->porosity_;
        }
        return this->porousPhases.porousPhases().at(phaseName).alpha;
    };
    auto getRho = [&](const word& phaseName) ->const volScalarField& {
        if(phaseName==porousPhaseInfo::FLUID_PHASE_NAME) {
            return this->rho_;
        }
        return this->porousPhases.porousPhases().at(phaseName).thermo->rho();
    };
    auto getCpv = [&](const word& phaseName) -> tmp<volScalarField> {
        if(phaseName==porousPhaseInfo::FLUID_PHASE_NAME) {
            return this->thermoPtr_->Cpv();
        }
        return this->porousPhases.porousPhases().at(phaseName).thermo->Cpv();
    };
    auto getKappa = [&](const word& phaseName) -> tmp<volScalarField> {
        if(phaseName==porousPhaseInfo::FLUID_PHASE_NAME) {
            return this->thermophysicalTransport->kappaEff();
        }
        return this->porousPhases.porousPhases().at(phaseName).thermo->kappa();
    };
    auto getTFieldRef = [&](const word& phaseName) -> volScalarField& {
        if(phaseName==porousPhaseInfo::FLUID_PHASE_NAME) {
            return this->thermoPtr_->T();
        }
        return this->porousPhases.porousPhases().at(phaseName).thermo->T();
    };

    volScalarField alphaRhoCp(
        IOobject(
            "alphaRhoCpSum",
            this->runTime.name(),
            this->mesh_, 
            IOobject::NO_READ,
            IOobject::NO_WRITE,
            false // no register
        ),
        this->mesh_,
        dimensionedScalar("rhoCpEffTemp",
            dimEnergy/dimVolume/dimTemperature,
            scalar(0)
        )
    );
    volScalarField alphaSum(
        IOobject(
            "alphaSum",
            this->runTime.name(),
            this->mesh_, 
            IOobject::NO_READ,
            IOobject::NO_WRITE,
            false // no register
        ),
        this->mesh_,
        dimensionedScalar("alphaSumTemp",
            dimless,
            scalar(0)
        )
    );
    std::vector<effectiveHeatConductivity::kappaInfo> kappaInfos;
    for(const word& phaseName: node.thermalEquilibriumPhaseNames) {
        alphaRhoCp += getAlpha(phaseName) * getRho(phaseName) * getCpv(phaseName);
        kappaInfos.emplace_back(
            getAlpha(phaseName),
            getKappa(phaseName)
        );
        alphaSum += getAlpha(phaseName);
    }
    tmp<volScalarField> kappaEff{nullptr};
    const bool singlePhase = node.thermalEquilibriumPhaseNames.size()==1;
    if(singlePhase) {
        kappaEff=kappaInfos[0].kappa;
    }else {
        kappaEff=node.effectiveKappaModel->kappaEff(kappaInfos);
    }
    // Build fvMatrix
    volScalarField&T = getTFieldRef(node.thermalEquilibriumPhaseNames[0]);
    fvScalarMatrix TEqn(
        alphaRhoCp*fvm::ddt(T)
        - fvm::laplacian(alphaSum*kappaEff, T)
        - fvModels().source(alphaRhoCp, T)
    );
    // add fluid terms
    const std::optional<size_t> fluidIndex = node.fluidPhaseIndex();
    if(fluidIndex) {
        const volScalarField& he = thermoPtr_->he();
        const bool internalEnergy = he.name() == "e";
        const volScalarField & dhedp_T = thermoPtr_->dhedp_T();
        auto Cpv = this->thermoPtr_->Cpv();
        const surfaceScalarField phiCpv =(fvc::interpolate(Cpv) * phi_)();
        const auto & alphaF = this->porosity_;
        TEqn += fvm::div(phiCpv, T) - fvm::SuSp(fvc::div(phiCpv), T)+ TEqnNonIdealityPressureTerm(dhedp_T);
        TEqn += alphaF*fvc::ddt(rho_, K) + fvc::div(phi_, K);
        TEqn += alphaF*pressureWork(
          internalEnergy
          ? fvc::div(phi_, p_()/rho_)()
          : -dpdt
        );

        if(buoyancy.valid()) {
            TEqn-= rho_*(U_ & buoyancy->g);
        }
    }
    // add phasewise heat transfer
    for(auto & htSource: node.heatTransferSources) {
        const word phaseDest = node.thermalEquilibriumPhaseNames[htSource.phaseA_index];
        const word phaseSrc = htSource.phaseB_name;
        const volScalarField& Tdest = getTFieldRef(phaseDest);
        const volScalarField& Tsrc = getTFieldRef(phaseSrc);
        const auto & htInfo = htSource.heatTransferInfo;
        const auto hsAs = getAlpha(phaseSrc)*getAlpha(phaseDest) * htInfo.heatTransferCoefficient * htInfo.effectiveSpecificSurfaceArea;
        TEqn -= hsAs*(Tsrc-Tdest);
    }

    return TEqn;
}

void solvers::porousMediaFluid::thermophysicalPredictor() {
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