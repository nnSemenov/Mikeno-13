
#include "argList.H"

#include "fluidThermo.H"
#include "fluidMulticomponentThermo.H"
#include "compressibleMomentumTransportModel.H"

#include "specie.H"

#include <cstddef>
#include <exception>
#include <memory>
#include <stdexcept>
#include <string>
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

    virtual ~pureTestData()=default;

    virtual void delete_data(size_t index) & {
        this->p.erase(this->p.begin()+index);
        this->T.erase(this->T.begin()+index);
        this->rho.erase(this->rho.begin()+index);
        this->Cp.erase(this->Cp.begin()+index);
    }

    virtual bool mutlicomponent() const {
        return false;
    }
};

struct mixtureTestData: public pureTestData {
    std::vector<std::vector<float>> Y_;

    virtual ~mixtureTestData()=default;

    void delete_data(size_t index) & override  {
        pureTestData::delete_data(index);
        for(auto & vec: Y_) {
            vec.erase(vec.begin()+index);
        }
    }

    bool mutlicomponent() const final {
        return true;
    }
};

enum class specie_name {
    // H2,
    NH3,
    H2O,
    // CH4,
    // N2,
};

constexpr size_t N_specie=2;

const std::vector<std::string> spNames = {
    // "H2",
    "NH3","H2O"
    // "CH4","N2"
};

std::unique_ptr<pureTestData> load_data(const std::string& filename);

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
    const auto data= load_data("data/"+eos+".csv");
    if(data==nullptr) {
        return 1;
    }

    autoPtr<fluidThermo> thermoPtr_;
    if(data->mutlicomponent()) {
        thermoPtr_=fluidMulticomponentThermo::New(mesh).ptr();
    }else {
        thermoPtr_=fluidThermo::New(mesh);
    }

    auto &p=thermoPtr_->p();
    auto &T=thermoPtr_->T();
    auto &Cp=thermoPtr_->Cp();

    if(data->T.size()>mesh.nCells()) {
        Info<<"No enough cells: required "<<data->T.size()<<", but only have "<<mesh.nCells()<<endl;
        return 1;
    }
    forAll(data->T, idx) {
        p[idx]=data->p[idx];
        T[idx]=data->T[idx];
    }
    if(data->mutlicomponent()) {
        const auto & Y=dynamic_cast<mixtureTestData*>(data.get())->Y_;
        auto & thermo=dynamic_cast<fluidMulticomponentThermo&>(thermoPtr_());
        auto & Y_dest=thermo.Y();
        for(size_t spIdx=0;spIdx<N_specie;spIdx++) {
            forAll(data->T, idx) {
                Y_dest[spIdx][idx]=Y[spIdx][idx];
            }
        }
        thermo.normaliseY();
    }
    // correct thermo
    thermoPtr_->he()=thermoPtr_->he(p,T);
    thermoPtr_->correct();

    auto rho=thermoPtr_->rho();

    relativeDiffRange rhoDiff, CpDiff;

    forAll(data->T, cell) {
        std::printf("p = %.1e Pa, T = %.2f K, ", p[cell],T[cell]);

        if(data->mutlicomponent()) {
            auto & thermo=dynamic_cast<fluidMulticomponentThermo&>(thermoPtr_());
            auto & Y_dest=thermo.Y();
            for(size_t spidx=0;spidx<N_specie;spidx++) {
                std::printf("Y_%s = %1.2e, ", spNames[spidx].c_str(), Y_dest[spidx][cell]);
            }
        }

        const scalar rhoRDiff=relativeDiff(rho()[cell], data->rho[cell]);
        rhoDiff.update(rhoRDiff);
        std::printf("rho diff = %1.2e, ",rhoRDiff);

        const scalar CpRelDiff=relativeDiff(Cp[cell], data->Cp[cell]);
        CpDiff.update(CpRelDiff);
        std::printf("Cp diff = %1.2e, ", CpRelDiff);
//        Info<<"rho test = "<<rho()[cell]<<" kg/cum, rho accurate = "<<data->rho[cell]<<" kg/cum, ";
//        Info<<"Cp = "<<Cp[cell]<<" J/kg/K\n";
        std::printf("\n");
    }
    std::printf("\n\n\n Summary:\n");
    std::printf("Relative diff of rho: [%1.2e, %1.2e]\n", rhoDiff.min, rhoDiff.max);
    std::printf("Relative diff of Cp: [%1.2e, %1.2e]\n", CpDiff.min, CpDiff.max);
//    Info<<endl;
    return 0;
}


std::unique_ptr<pureTestData> load_data(const std::string& filename) {

    std::unique_ptr<pureTestData> ret{nullptr};
    try {
        rapidcsv::Document csv(filename);
    
        const bool contains_specie=[&csv]() {
            const auto cols=csv.GetColumnNames();
            for(const auto & colName:cols) {
                if (colName=="Y_H2O") {
                    return true;
                }
            }
            return false;
        }();
    
        if(not contains_specie) {
            ret =std::make_unique<pureTestData>();
        }
        else {
            ret= std::make_unique<mixtureTestData>();
        }
    
        ret->T=csv.GetColumn<float>("T/K");
        ret->p=csv.GetColumn<float>("p/Pa");
        ret->Cp=csv.GetColumn<float>("CP/J/kg/K");
        ret->rho=csv.GetColumn<float>("rho/kg/cum");
    
        const size_t N_data=ret->T.size();
    
        if (contains_specie) {
            mixtureTestData& data=dynamic_cast<mixtureTestData&>(*ret);
            data.Y_.resize(N_specie);
            for(size_t spIdx=0;spIdx<N_specie;spIdx++) {
                std::string colName="Y_"+spNames[spIdx];
                data.Y_[spIdx]=csv.GetColumn<float>(colName);
            }
            // normalize data
            for(size_t idx=0;idx<N_data;idx++) {
                scalar Ysum=0;
                for(size_t spIdx=0;spIdx<N_specie;spIdx++) {
                    Ysum+=data.Y_[spIdx][idx];
                }
                if(not (Ysum>0)) {
                    throw std::runtime_error("Found non-positive Y sum = "+std::to_string(Ysum));
                }

                for(size_t spIdx=0;spIdx<N_specie;spIdx++) {
                    data.Y_[spIdx][idx]/=Ysum;
                }
            }
        }
    
        std::vector<size_t> erase_idx;
        for(size_t idx=0;idx<N_data;idx++) {
            if(not(ret->rho[idx]>0) or not(ret->Cp[idx]>0)) {
                erase_idx.emplace_back(idx);
                continue;
            }
            if(ret->T[idx]>5000) {
                erase_idx.emplace_back(idx);
                continue;
            }
        }
    
        for(auto it=erase_idx.rbegin();it not_eq erase_idx.rend();++it) {
            ret->delete_data(*it);
        }
    
        std::printf("Erased %zu from %zu lines\n",erase_idx.size(), N_data);

    } catch(const std::exception&e) {
        std::fprintf(stderr,"Exception: %s\n",e.what());
        return nullptr;
    }


    return ret;
}