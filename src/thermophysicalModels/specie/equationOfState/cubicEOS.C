//
// Created by joseph on 25-7-15.
//
#include "cubicEOS.H"
#include "dictionary.H"

#include <limits>

using Foam::scalar;
using Foam::word;
using Foam::vanDerWaals_solution;


std::variant<vanDerWaals_solution,scalar> Foam::solveCubicEquation(scalar a2, scalar a1, scalar a0) {
  const scalar Q = (3 * a1 - a2 * a2) / 9.0;
  const scalar Rl = (9 * a2 * a1 - 27 * a0 - 2 * a2 * a2 * a2) / 54.0;

  const scalar Q3 = Q * Q * Q;
  const scalar D = Q3 + Rl * Rl;

//  scalar root = -1;

  if (D <= 0) {
    const scalar th = ::acos(Rl / sqrt(-Q3));
    const scalar qm = 2 * sqrt(-Q);
    const scalar r1 = qm * cos(th / 3.0) - a2 / 3.0;
    const scalar r2 =
        qm * cos((th + 2 * constant::mathematical::pi) / 3.0) - a2 / 3.0;
    const scalar r3 =
        qm * cos((th + 4 * constant::mathematical::pi) / 3.0) - a2 / 3.0;

    vanDerWaals_solution sol{};
    sol.x_max=max(r1, max(r2, r3));
    sol.x_min=min(r1, min(r2, r3));
    sol.x_middle=min(max(r2,r3),max(min(r2,r3),r1));
    assert(sol.x_min<=sol.x_middle);
    assert(sol.x_middle<=sol.x_max);
    assert(sol.x_min>0);
    return sol;
//    root = max(r1, max(r2, r3));
  } else {
    // One root is real
    const scalar D05 = sqrt(D);
    const scalar S = cbrt(Rl + D05);
    scalar Tl = 0;
    if (D05 > Rl) {
      Tl = -cbrt(mag(Rl - D05));
    } else {
      Tl = cbrt(Rl - D05);
    }

    const scalar root = S + Tl - a2 / 3.0;
    assert(root > 0);

    return root;
  }
}


Foam::scalar Foam::solveCubicEquation(scalar a2, scalar a1, scalar a0, bool prefer_max) {
  const auto result= solveCubicEquation(a2,a1,a0);
  const vanDerWaals_solution* vdw=std::get_if<vanDerWaals_solution>(&result);
  if(vdw) {
    if (prefer_max) {
      return vdw->x_max;
    }
    return vdw->x_min;
  }
  return std::get<scalar>(result);
}

word Foam::parseBinarySpeciePair(const word&str, word&sp0, word&sp1) {
    sp0="";
    sp1="";
    const word explain="it is not a valid binary specie pair. Example: \"O2:CO2\"";
//    const std::string_view str{str__};
    const size_t comma_idx=str.find_first_of(':');
    if(comma_idx==str.npos) {
        return str+" doesn't contain colon, "+explain;
    }
    if(comma_idx not_eq str.find_last_of(':')) {
        return str+" has multiple colon, "+explain;
    }
    sp0=std::string{str.data(),str.data()+comma_idx};
    sp1=std::string{str.begin()+comma_idx+1,str.end()};
    return "";
}

void Foam::parseBinaryInteractionMatrix(const dictionary&kDict,
                                        const std::function<bool(const word&)> & skipKey,
                                        flatMatrix& mat,
                                        const speciesTable&spTable,
                                        bool symmetry) {

    for(scalar &k:mat) {
        k=std::numeric_limits<scalar>::signaling_NaN();
    }

    auto set_k_ij=[&mat](label i, label j, scalar k) noexcept  {
            const bool alreadySet=std::isfinite(mat(i,j));
            if(alreadySet) {
                WarningInFunction<<"Duplicated declaration of k("<<i<<','<<j<<"), previous value will be covered."<<endl;
            }
            mat(i,j)=k;
    };
    const auto keys = kDict.keys(true);
    forAll(keys, keyIdx) {
        const word & speciePair=keys[keyIdx];
        if(skipKey(speciePair)) {
            continue;
        }
        word sp0, sp1;
        const word err=parseBinarySpeciePair(speciePair,sp0,sp1);
        if(not err.empty()) {
            FatalErrorInFunction<<"Invalid binary interaction table: "<<err<<endl;
            ::Foam::abort(::Foam::FatalError);
        }
        const label idxSp0=spTable[sp0];
        const label idxSp1=spTable[sp1];

        const scalar k=kDict.template lookup<scalar>(speciePair);
        set_k_ij(idxSp0,idxSp1,k);
        if(symmetry) {
            set_k_ij(idxSp1,idxSp0,k);
        }
    }
    for(scalar& k:mat) {
        if(not std::isfinite(k)) {
            k=0;
        }
    }
}