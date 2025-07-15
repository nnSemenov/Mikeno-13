//
// Created by joseph on 25-7-11.
//

#ifndef CUBICEOS_H
#define CUBICEOS_H

#include "autoPtr.H"
#include "mathematicalConstants.H"
#include "speciesTable.H"
#include <cassert>
#include <type_traits>
#include <functional>

namespace Foam {

    struct cubicEOSDimlessCoefficient {
        scalar A;
        scalar B;
    };

    // Solve z^3 + a2 *z^2 + a1 * z + z0 = 0
    scalar solveCubicEquation(scalar a2, scalar a1, scalar a0);

    struct residualEnergy {
        scalar h_R;//[J/kg]
        scalar e_R;//[J/kg]
        scalar Z;
    };

    struct residualSpecificHeat {
        scalar Cp_R;//[J/kg/K]
        scalar Cv_R;//[J/kg/K]
        scalar Cp_R_minus_Cv_R;//[J/kg/K]
        scalar Z;
    };

    namespace internal {
        // Some SFINAE tricks
        template<class EOS>
        inline int requiresCubicEOS(const EOS *eos) {
            const scalar T = 273;
            const scalar p = 1e5;
            const scalar W = 28.0;
            // EOS must have these interfaces
            [[maybe_unused]] typename EOS::EOSCore core = eos->core(p, T);
            [[maybe_unused]] const scalar u = core.Z(p, T) + core.rho(p, T, W)
                                              + core.h(p, T, W) + core.Cp(p, T, W) + core.e(p, T, W) +
                                              core.Cv(p, T, W) + core.sp(p, T, W) + core.sv(p, T, W) +
                                              core.psi(p, T, W) + core.CpCv(p, T, W) + core.alphav(p, T, W);
        }

        inline void requiresCubicEOS(...) {}

    }
    template<class EOS>
    struct is_cubic_EOS {
        static constexpr bool value = std::is_same<decltype(internal::requiresCubicEOS(
                static_cast<const EOS *>(nullptr)
        )), int>::value and (not EOS::incompressible);
    };

    class flatMatrix {
    protected:
        label rowCols;
        List<scalar> value;

    public:
        explicit flatMatrix(label rc): rowCols(rc),value(rc*rc, Foam::zero()) {
        }

        inline scalar rows() const {
            return this->rowCols;
        }
        inline scalar cols() const {
            return this->rowCols;
        }
        inline scalar size() const {
            return this->rows()*this->cols();
        }


        inline label offsetOf(label i, label j) const {
            assert(rowCols>0);
            assert(i>=0);
            assert(j>=0);
            assert(i<rowCols);
            assert(j<rowCols);
            return i*rowCols+j;
        }

        inline scalar & operator()(label i,label j) & {
            return this->value[this->offsetOf(i,j)];
        }

        inline const scalar & operator()(label i,label j)const & {
            return this->value[this->offsetOf(i,j)];
        }

        inline List<scalar>& asList() & {
            return this->value;
        }
        inline const List<scalar>& asList() const & {
            return this->value;
        }

        inline auto begin() & {
            return this->value.begin();
        }
        inline auto end() & {
            return this->value.end();
        }
        inline auto begin()const & {
            return this->value.begin();
        }
        inline auto end()const & {
            return this->value.end();
        }
    };

    word parseBinarySpeciePair(const word&str, word&sp0, word&sp1);

    void parseBinaryInteractionMatrix(const dictionary&coeffDict, const std::function<bool(const word&)> & skipKey,
                                      flatMatrix& mat, const speciesTable&spTable,
                                      bool symmetry);
}

#endif // CUBICEOS_H
