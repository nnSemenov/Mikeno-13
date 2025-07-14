//
// Created by joseph on 25-7-11.
//

#ifndef RedlichKwongGas_H
#define RedlichKwongGas_H

#include "autoPtr.H"
#include "../equationOfState/cubicEOS.H"

namespace Foam {

template<class Specie> class RedlichKwongGas;

template<class Specie>
inline RedlichKwongGas<Specie> operator+
(
        const RedlichKwongGas<Specie>&,
        const RedlichKwongGas<Specie>&
);

template<class Specie>
inline RedlichKwongGas<Specie> operator*
(
        const scalar,
        const RedlichKwongGas<Specie>&
);

template<class Specie>
inline RedlichKwongGas<Specie> operator==
(
        const RedlichKwongGas<Specie>&,
        const RedlichKwongGas<Specie>&
);

template<class Specie>
Ostream& operator<<
(
        Ostream&,
        const RedlichKwongGas<Specie>&
);

template<class Specie>
class RedlichKwongGas : public Specie {

public:

    struct EOSCore {
        cubicEOSRawCoefficient rawCoeff;

    protected:
        //- Molar volume [m^3/kmol]
    public:
        inline cubicEOSDimlessCoefficient dimlessCoeff(scalar p, scalar T) const {
            const scalar A = rawCoeff.a / p / sqrt(T) * sqr(p / (RR * T));
            const scalar B = rawCoeff.b * p / (RR * T);
            return {A, B};
        }
        // compute from AB, that is real EOSCore
        inline scalar Z(const cubicEOSDimlessCoefficient&AB) const {
            const scalar A = AB.A;
            const scalar B = AB.B;

            const scalar a2 = -1;
            const scalar a1 = A - B - sqr(B);
            const scalar a0 = -A * B;

            return solveCubicEquation(a2, a1, a0);
        }
        //- Return residual h and e
        inline Foam::residualEnergy residualHE(const scalar p, const scalar T, scalar W) const {
            const auto coeff = this->dimlessCoeff(p, T);

            const scalar A = coeff.A;
            const scalar B = coeff.B;
            const scalar Z = this->Z(coeff);

            const scalar e_R_dimless = -(3 * A) / (2 * B) * log(Z / (Z + B));
            const scalar h_R_dimless =
                    (Z - 1)
                    + e_R_dimless;
            const scalar e_R = T * this->R(W) * e_R_dimless;
            const scalar h_R = T * this->R(W) * h_R_dimless;
            return Foam::residualEnergy{h_R, e_R, Z};
        }

        //- Return residual Cp and Cv
        inline Foam::residualSpecificHeat residualSpecificHeat(const scalar p, const scalar T, scalar W) const {
            const auto coeff = this->dimlessCoeff(p, T);

            const scalar A = coeff.A;
            const scalar B = coeff.B;
            const scalar Z = this->Z(coeff);
            const scalar Cv_dimless = (3 * A) / (4 * B) * log(1 + B / Z);

            const scalar CpRMCvR_dimless =
                    -1 -
                    sqr(1 / (Z - B) + A / (2 * Z * (Z + B)))
                    /
                    (-1 / sqr(Z - B) + A * (2 * Z + B) / sqr(Z) / sqr(Z + B));
            const scalar Cp_dimless = Cv_dimless + CpRMCvR_dimless;

            return Foam::residualSpecificHeat{
                    Cp_dimless * this->R(W),
                    Cv_dimless * this->R(W),
                    CpRMCvR_dimless * this->R(W),
                    Z
            };
        }

        inline scalar R(scalar W) const {
            return RR/W;
        }
        // compute from p and T
        inline scalar Z(scalar p, scalar T) const {
            auto AB=this->dimlessCoeff(p,T);
            return this->Z(AB);
        }

        inline scalar rho(scalar p, scalar T, scalar W) const {
            const scalar Z=this->Z(p,T);
            return p / (Z * this->R(W) * T);
        }

        //- Return enthalpy contribution [J/kg]
        inline scalar h(const scalar p, const scalar T, scalar W) const {
            return this->residualHE(p,T,W).h_R;
        }
        //- Return internal energy contribution [J/kg]
        inline scalar e(const scalar p, const scalar T, scalar W) const {
            return this->residualHE(p,T,W).e_R;
        }

        //- Return Cp contribution [J/(kg K]
        inline scalar Cp(scalar p, scalar T, scalar W) const {
            return this->residualSpecificHeat(p,T,W).Cp_R;
        }


        //- Return Cv contribution [J/(kg K]
        inline scalar Cv(scalar p, scalar T, scalar W) const{
            return this->residualSpecificHeat(p,T,W).Cv_R;
        }

        //- Return entropy contribution to the integral of Cp/T [J/kg/K]
        inline scalar sp(const scalar p, const scalar T, scalar W) const {
            return 0;
        }

        //- Return entropy contribution to the integral of Cv/T [J/kg/K]
        inline scalar sv(const scalar p, const scalar T, scalar W) const {
            return 0;
        }

        //- Return compressibility [s^2/m^2]
        inline scalar psi(scalar p, scalar T, scalar W) const {
            return 1/(this->Z(p,T)*this->R(W)*T);
        }

        //- Return (Cp - Cv) [J/(kg K]
        inline scalar CpMCv(scalar p, scalar T, scalar W) const{
            return this->residualSpecificHeat(p,T,W).Cp_R_minus_Cv_R;
        }

        //- Return volumetric coefficient of thermal expansion [1/T]
        inline scalar alphav(const scalar p, const scalar T) const;
    };

public:
    inline RedlichKwongGas(
            const Specie &sp
       );

    template<class getRawCoeffFun, class getXiFun>
    static inline cubicEOSRawCoefficient mixingRule(label nSpecie, getRawCoeffFun &rawCoeffFun, getXiFun &specieMoleFracFun) {
        return mixingRuleRK(nSpecie,rawCoeffFun,specieMoleFracFun);
    }

    RedlichKwongGas(const word&name, const dictionary&dict);

    inline RedlichKwongGas(const word&name, const RedlichKwongGas&);

    inline autoPtr<RedlichKwongGas> clone() const;


    // Member Functions

    //- Return the instantiated type name
    static word typeName()
    {
        return "RedlichKwongGas<" + word(Specie::typeName_()) + '>';
    }
    inline Foam::cubicEOSRawCoefficient coeffRaw(scalar p, scalar T) const;

    inline EOSCore core(scalar p, scalar T) const {
        return EOSCore{this->coeffRaw(p,T)};
    }

    //- Is the equation of state is incompressible i.e. rho != f(p)
    static const bool incompressible = false;

    //- Is the equation of state is isochoric i.e. rho = const
    static const bool isochoric = false;

    //- Return compression factor []
    inline scalar Z(scalar p, scalar T) const{
        return this->core(p,T).Z(p,T);
    }

    //- Return density [kg/m^3]
    inline scalar rho(scalar p, scalar T) const {
        return this->core(p,T).rho(p,T,this->W());
    }

    //- Return enthalpy contribution [J/kg]
    inline scalar h(const scalar p, const scalar T) const {
        return this->core(p,T).h(p,T,this->W());
    }

    //- Return Cp contribution [J/(kg K)]
    inline scalar Cp(scalar p, scalar T) const{
        return this->core(p,T).Cp(p,T,this->W());
    }

    //- Return internal energy contribution [J/kg]
    inline scalar e(const scalar p, const scalar T) const{
        return this->core(p,T).e(p,T,this->W());
    }

    //- Return Cv contribution [J/(kg K)]
    inline scalar Cv(scalar p, scalar T) const{
        return this->core(p,T).Cv(p,T,this->W());
    }

    //- Return entropy contribution to the integral of Cp/T [J/kg/K]
    inline scalar sp(const scalar p, const scalar T) const {
        return this->core(p,T).sp(p,T,this->W());
    }

    //- Return entropy contribution to the integral of Cv/T [J/kg/K]
    inline scalar sv(const scalar p, const scalar T) const{
        return this->core(p,T).sv(p,T,this->W());
    }

    //- Return compressibility [s^2/m^2]
    inline scalar psi(scalar p, scalar T) const{
        return this->core(p,T).psi(p,T,this->W());
    }

    //- Return (Cp - Cv) [J/(kg K]
    inline scalar CpMCv(scalar p, scalar T) const{
        return this->core(p,T).CpMCv(p,T,this->W());
    }

    //- Return volumetric coefficient of thermal expansion [1/T]
    inline scalar alphav(const scalar p, const scalar T) const{
        return this->core(p,T).alphav(p,T,this->W());
    }

    // IO

    //- Write to Ostream
    void write(Ostream& os) const;

    // Member Operators

    inline void operator+=(const RedlichKwongGas&);
    inline void operator*=(const scalar);


    // Friend operators

    friend RedlichKwongGas operator+ <Specie>
            (
                    const RedlichKwongGas&,
                    const RedlichKwongGas&
            );

    friend RedlichKwongGas operator* <Specie>
            (
                    const scalar s,
                    const RedlichKwongGas&
            );

    friend RedlichKwongGas operator== <Specie>
            (
                    const RedlichKwongGas&,
                    const RedlichKwongGas&
            );


    // Ostream Operator

    friend Ostream& operator<< <Specie>
            (
                    Ostream&,
                    const RedlichKwongGas&
            );
};

} // End namespace Foam


#include "RedlichKwongGasI.H"

#ifdef NoRepository
#include "RedlichKwongGas.C"
#endif

#endif //RedlichKwongGas_H
