
#include "argList.H"

#include "fluidThermo.H"
#include "compressibleMomentumTransportModel.H"

#include "specie.H"

#include <vector>
#include <rapidcsv.h>
#include <cstdio>

using Foam::scalar;
using Foam::List;
using Foam::scalarList;

struct pureTestData {
    std::vector<float> p;
    std::vector<float> T;
    std::vector<float> rho;
    std::vector<float> Cp;
};

pureTestData load_data(const std::string& filename);

scalar relativeDiff(const scalar value, const scalar accurate) {
    return (value-accurate)/accurate;
}

struct relativeDiffRange {
    scalar min{0};
    scalar max{0};

    void update(scalar rDiff) {
        this->min=Foam::min(this->min,rDiff);
        this->max=Foam::max(this->max,rDiff);
    }
};

int main(int argc, char*argv[]) {
    using namespace Foam;

    argList::addOption(
        "eos",
        "name",
        "Equation of state for thermodynamic"
    );

    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"

    const word eos = args.option("eos");

    autoPtr<fluidThermo> thermoPtr_=fluidThermo::New(mesh);

    auto &p=thermoPtr_->p();
    auto &T=thermoPtr_->T();
    auto &Cp=thermoPtr_->Cp();

    const auto data= load_data("data/"+eos+".csv");
    if(data.T.size()>mesh.nCells()) {
        Info<<"No enough cells: required "<<data.T.size()<<", but only have "<<mesh.nCells()<<endl;
        return 1;
    }
    forAll(data.T, idx) {
        p[idx]=data.p[idx];
        T[idx]=data.T[idx];
    }
    // correct thermo
    thermoPtr_->he()=thermoPtr_->he(p,T);
    thermoPtr_->correct();

    auto rho=thermoPtr_->rho();

    relativeDiffRange rhoDiff, CpDiff;

    forAll(data.T, cell) {
        std::printf("p = %.1e Pa, T = %.2f K, ", p[cell],T[cell]);
        const scalar rhoRDiff=relativeDiff(rho()[cell], data.rho[cell]);
        rhoDiff.update(rhoRDiff);
        std::printf("rho diff = %1.2e, ",rhoRDiff);

        const scalar CpRelDiff=relativeDiff(Cp[cell], data.Cp[cell]);
        CpDiff.update(CpRelDiff);
        std::printf("Cp diff = %1.2e, ", CpRelDiff);
//        Info<<"rho test = "<<rho()[cell]<<" kg/cum, rho accurate = "<<data.rho[cell]<<" kg/cum, ";
//        Info<<"Cp = "<<Cp[cell]<<" J/kg/K\n";
        std::printf("\n");
    }
    std::printf("\n\n\n Summary:\n");
    std::printf("Relative diff of rho: [%1.2e, %1.2e]\n", rhoDiff.min, rhoDiff.max);
    std::printf("Relative diff of Cp: [%1.2e, %1.2e]\n", CpDiff.min, CpDiff.max);
//    Info<<endl;
    return 0;
}


pureTestData load_data(const std::string& filename) {
    pureTestData ret;
    rapidcsv::Document csv(filename);
    ret.T=csv.GetColumn<float>("T/K");
    ret.p=csv.GetColumn<float>("p/Pa");
    ret.Cp=csv.GetColumn<float>("CP/J/kg/K");
    ret.rho=csv.GetColumn<float>("rho/kg/cum");
    return ret;
}