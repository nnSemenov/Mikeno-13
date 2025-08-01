#ifndef porousMediaFluid_H
#define porousMediaFluid_H

#include "fluid.H"
#include "solidThermophysicalTransportModel.H"
#include <map>

namespace Foam {

class porousPhaseInfo {
public:
    struct porousPhase {
        volScalarField alpha;
        autoPtr<solidThermo> thermo;
        autoPtr<solidThermophysicalTransportModel> thermophysicalTransport;
    };

protected:
    std::map<word, porousPhase> porousPhases_;

public:
    explicit porousPhaseInfo(fvMesh&mesh, const Time& runTime);
    porousPhaseInfo(const porousPhaseInfo&)=delete;
    ~porousPhaseInfo()=default;

    auto& porousPhases() & {
        return porousPhases_;
    }
    
    const auto& porousPhases() const & {
        return porousPhases_;
    }
};

namespace solvers {

class porousMediaFluid : public fluid {
protected:


    volVectorField U_physical;
    volScalarField porosity_;
    porousPhaseInfo porousPhases;

    void updatePorosity();
    
    tmp<volScalarField::Internal> TEqnNonIdealityPressureTerm(const volScalarField& dhedp_T) const;
public:
    TypeName("porousMediaFluid");

    // Constructors
    porousMediaFluid(fvMesh & mesh);

    porousMediaFluid(const porousMediaFluid&)=delete;

    // tmp<volScalarField> porosity() const;

    ~porousMediaFluid() override;

    void momentumPredictor() override;

    void thermophysicalPredictor() override;

    // void prePredictor() override;
  
    // void postCorrector() override;


    //- Disallow default bitwise assignment
    void operator=(const porousMediaFluid&) = delete;
};

}
}

#endif