#ifndef porousMediaFluid_H
#define porousMediaFluid_H

#include "fluid.H"
#include "porousPhaseInfo.H"

namespace Foam {


namespace solvers {

class porousMediaFluid : public fluid {
protected:


    volVectorField U_physical;
    volScalarField porosity_;
    porousPhaseInfo porousPhases;

    void updatePorosity();
    
    tmp<volScalarField::Internal> TEqnNonIdealityPressureTerm(const volScalarField& dhedp_T) const;

    tmp<fvScalarMatrix> TEqnCore(porousPhaseInfo::heatTransferInfoNode& node);
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