/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2014-2023 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::PengRobinsonGas

Description
    PengRobinsonGas cubic equation of state for gases

    Coefficient mixing is very inaccurate and not supported, so this equation of
    state can only be applied to mixtures by using a thermophysical properties
    model which mixes specie property value.

Usage
    \table
        Property     | Description
        Tc           | Critical temperature [K]
        Vc           | Critical volume [m^3/kmol]
        Pc           | Critical pressure [Pa]
        omega        | Acentric factor [-]
    \endtable

    Example specification of the PengRobinsonGas equation of state for methane:
    \verbatim
    equationOfState
    {
        Tc        190.55;
        Vc        0.0285;
        Pc        4.595e6;
        omega     0.0115;

    }
    \endverbatim

SourceFiles
    PengRobinsonGasI.H
    PengRobinsonGas.C

\*---------------------------------------------------------------------------*/

#ifndef PengRobinsonGas_H
#define PengRobinsonGas_H

#include "autoPtr.H"
#include "speciesTable.H"
#include "../equationOfState/cubicEOS.H"
#include <cmath>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam {

// Forward declaration of friend functions and operators

    template<class Specie>
    class PengRobinsonGas;

    template<class Specie>
    inline PengRobinsonGas<Specie> operator+
            (
                    const PengRobinsonGas<Specie> &,
                    const PengRobinsonGas<Specie> &
            );

    template<class Specie>
    inline PengRobinsonGas<Specie> operator*
            (
                    const scalar,
                    const PengRobinsonGas<Specie> &
            );

    template<class Specie>
    inline PengRobinsonGas<Specie> operator==
            (
                    const PengRobinsonGas<Specie> &,
                    const PengRobinsonGas<Specie> &
            );

    template<class Specie>
    Ostream &operator<<
            (
                    Ostream &,
                    const PengRobinsonGas<Specie> &
            );


/*---------------------------------------------------------------------------*\
                       Class PengRobinsonGas Declaration
\*---------------------------------------------------------------------------*/

    template<class Specie>
    class PengRobinsonGas
            :
                    public Specie {
        // Private Data

    public:

        struct EOSCore {
            scalar a;
            scalar b;
            scalar da_dT;
            scalar dd2a_dT2;

            inline cubicEOSDimlessCoefficient dimlessCoeff(scalar p, scalar T) const {
                const scalar A = a * p / sqr(RR * T);
                const scalar B = b * p / (RR * T);
                return {A,B};
            }

            inline scalar R(scalar W) const {
                return RR/W;
            }

            inline scalar Z(const cubicEOSDimlessCoefficient&AB) const {
                const scalar A = AB.A;
                const scalar B = AB.B;

                const scalar a2 = B-1;
                const scalar a1=A -2*B -3*sqr(B);
                const scalar a0 = pow3(B) + sqr(B)-A*B;
                return solveCubicEquation(a2,a1,a0);
            }

            inline scalar Z(scalar p, scalar T) const {
                auto AB=this->dimlessCoeff(p,T);
                return this->Z(AB);
            }

            inline scalar rho(scalar p, scalar T, scalar W) const {
                const scalar Z=this->Z(p,T);
                return p / (Z * this->R(W) * T);
            }

            inline Foam::residualEnergy residualHE(scalar p, scalar T, scalar W) const {
                const auto AB=this->dimlessCoeff(p,T);
                const scalar A=AB.A;
                const scalar B=AB.B;
                const scalar Z=this->Z(AB);

                const scalar log_part = log(
                        (Z-(sqr(2.0)-1)*B)
                        /(Z+(sqr(2.0)+1)*B)
                        );
                const scalar aT_part = a - T*this->da_dT;
                const scalar e_R_dimless = 1/(2* sqr(2.0)*b*RR*T)*aT_part*log_part;
//                const scalar AT_part = A- sqr(RR)* pow3(T)/p * this->da_dT;
//
//                const scalar e_R_dimless = 1/(2* sqr(2.0)*B) * AT_part*log_part;
                const scalar h_R_dimless = Z-1 + e_R_dimless;
                return Foam::residualEnergy{
                        T * this->R(W) * h_R_dimless,
                        T * this->R(W) * e_R_dimless,
                        Z
                };
            }

            inline Foam::residualSpecificHeat residualSpecificHeat(scalar p, scalar T, scalar W) const {
                const auto AB=this->dimlessCoeff(p,T);
                const scalar B=AB.B;
                const scalar Z=this->Z(AB);

                const scalar log_part = log(
                        (Z-(sqr(2.0)-1)*B)
                        /(Z+(sqr(2.0)+1)*B)
                );
                const scalar pB_part = p*B/(2* sqr(2.0)* sqr(RR));

                const scalar Cv_dimless = -this->dd2a_dT2*pB_part*log_part;

                // compute CpMCv
                const scalar CpMCv_dimless = [=](){
                    const scalar V = Z*RR*T/p;
                    const scalar VVBbbVb=V*(V+b)+b*(V-b);
                    const scalar numerator = sqr(
                        RR/(V-b)
                        - da_dT/VVBbbVb
                    );
                    const scalar denominator =
                            2*a*(V+b)/sqr(VVBbbVb) - RR*T/ sqr(V-b);
                    return -1 - T/RR * numerator/denominator;
                }();
                const scalar Cp_dimless = Cv_dimless+CpMCv_dimless;

                return Foam::residualSpecificHeat{
                        Cp_dimless * this->R(W),
                        Cv_dimless * this->R(W),
                        CpMCv_dimless * this->R(W),
                        Z
                };
            }

            inline scalar e(scalar p, scalar T, scalar W) const {
                return this->residualHE(p,T,W).e_R;
            }

            inline scalar h(scalar p, scalar T, scalar W) const {
                return this->residualHE(p,T,W).h_R;
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

            inline scalar alphav(const scalar p, const scalar T) const;
        };

    public:
        // Constructors

        //- Construct from components
        inline PengRobinsonGas(
                    const Specie &sp
                );

        //- Construct from name and dictionary
        PengRobinsonGas(const word &name, const dictionary &dict);

        //- Construct as named copy
        inline PengRobinsonGas(const word &name, const PengRobinsonGas &);

        //- Construct and return a clone
        inline autoPtr<PengRobinsonGas> clone() const;


        // Member Functions

        //- Return the instantiated type name
        static word typeName() {
            return "PengRobinsonGas<" + word(Specie::typeName_()) + '>';
        }

        // Fundamental properties
        inline EOSCore core(scalar p, scalar T) const {
            const auto Tc = this->Tc();
            const auto Pc = this->Pc();
            const scalar omega=this->omega_;
            const scalar Tr = T/Tc;
            const scalar a_c = 0.457235* sqr(RR*Tc)/Pc;
            const scalar kappa = 0.37464+1.54226*omega - 0.26992*sqr(omega);
            const scalar sqrtAlpha = 1+kappa*(1-sqrt(Tr));
            const scalar alpha= sqr(sqrtAlpha);
            const scalar a = a_c*alpha;
            const scalar b =0.077796*RR*Tc/Pc;

            const scalar da_dT = -a_c*kappa* sqrt(alpha/(T*Tc));
            const scalar d2a_dT2 =
                    a_c*kappa*sqrtAlpha/(2* sqr(Tc)*Tr*sqr(Tr))
                    + 1/(2*alpha)*da_dT;

            return {a,b,da_dT,d2a_dT2};
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

        // mixing

        class EOSMixer {
        protected:
            const label nSpecie;
            // row major
            flatMatrix kij;
            explicit EOSMixer(label nSp):nSpecie(nSp), kij(nSp) { }
        public:
            EOSMixer(const speciesTable &spTable, const dictionary&physicalPropDict):
                EOSMixer(spTable.size()) {
                const dictionary* mixingRuleDict=physicalPropDict.subDictPtr("mixingRule");
                if(mixingRuleDict==nullptr) { // keep default, all k_ij=0
                    return;
                }
                const dictionary* binaryInterfactionDict=mixingRuleDict->subDictPtr("binaryInteraction");
                if(binaryInterfactionDict==nullptr) {
                    return;
                }
                const dictionary*kDict=binaryInterfactionDict->subDictPtr("k");
                if(kDict==nullptr) {
                    return;
                }
                const bool symmetry=kDict->lookupOrDefault<bool>("symmetry", true);

                auto skipFun=[](const word&key) {
                    if(key=="symmetry") {
                        return true;
                    }
                    return false;
                };
                parseBinaryInteractionMatrix(*kDict,skipFun,this->kij,spTable,symmetry);

                Info<<"Binary interaction coefficient table for PR equationOfState: \nk="<<this->kij.asList()<<endl;
            }

            inline scalar &k(label i, label j)& {
                return this->kij(i,j);
            }
            inline scalar k(label i,label j) const &{
                return this->kij(i,j);
            }

            template<class getCoreFun, class getXiFun>
            inline EOSCore mix(label nSpecie,
                               getCoreFun &coreFun,
                               getXiFun &specieMoleFracFun)const {

                scalar aSum=0;
                scalar da_dT_sum=0;
                scalar d2a_dT2_sum=0;
                scalar bSum=0;
                for(label i=0;i<nSpecie;i++) {
                    const scalar Xi=specieMoleFracFun(i);
                    const EOSCore iCore=coreFun(i);

                    bSum+=Xi*iCore.b;

                    for(label j=0;j<nSpecie;j++) {
                        const scalar Xj=specieMoleFracFun(j);
                        const EOSCore jCore=coreFun(j);
                        const scalar kij=this->k(i,j);
                        const scalar sqrt_aiaj=sqrt(iCore.a * jCore.a);
                        const scalar ddT_aiaj = iCore.a*jCore.da_dT + jCore.a*iCore.da_dT;
                        aSum += Xi*Xj*(1-kij)*sqrt_aiaj ;

                        // compute da/dT
                        const scalar ddT_sqrt_aiaj=1/(2*sqrt_aiaj)*ddT_aiaj;
                        da_dT_sum+= Xi*Xj*(1-kij) * ddT_sqrt_aiaj;

                        // compute d2a/dT2
                        const scalar d2_dT2_sqrt_aiaj = 1/(4*iCore.a * jCore.a) * (
                                2*sqrt_aiaj*(iCore.a *jCore.dd2a_dT2 + 2*iCore.da_dT*jCore.da_dT + jCore.a*iCore.dd2a_dT2)
                                - ddT_aiaj * ddT_sqrt_aiaj
                        );
                        d2a_dT2_sum += Xi*Xj*(1-kij) *d2_dT2_sqrt_aiaj;
                    }
                }
                return EOSCore{aSum,bSum,da_dT_sum,d2a_dT2_sum};
            }

        };

        // IO

        //- Write to Ostream
        void write(Ostream &os) const;

        // Member Operators

        inline void operator+=(const PengRobinsonGas &);

        inline void operator*=(const scalar);


        // Friend operators

        friend PengRobinsonGas operator+<Specie>
                (
                        const PengRobinsonGas &,
                        const PengRobinsonGas &
                );

        friend PengRobinsonGas operator*<Specie>
                (
                        const scalar s,
                        const PengRobinsonGas &
                );

        friend PengRobinsonGas operator==<Specie>
                (
                        const PengRobinsonGas &,
                        const PengRobinsonGas &
                );


        // Ostream Operator

        friend Ostream &operator<<<Specie>
                (
                        Ostream &,
                        const PengRobinsonGas &
                );
    };


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "PengRobinsonGasI.H"

#ifdef NoRepository
#include "PengRobinsonGas.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
