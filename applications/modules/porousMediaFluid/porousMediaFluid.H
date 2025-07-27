#ifndef porousMediaFluid_H
#define porousMediaFluid_H

#include "fluid.H"
#include "solidThermophysicalTransportModel.H"

namespace Foam {
namespace solvers {

class porousMediaFluid : public fluid {
protected:

    struct porousPhase {
        volScalarField alpha;
        autoPtr<solidThermo> thermo;
        autoPtr<solidThermophysicalTransportModel> thermophysicalTransport;
    };

    std::vector<porousPhase> porousPhases;

    volVectorField U_physical;
    volScalarField porosity_;

    void updatePorosity();
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