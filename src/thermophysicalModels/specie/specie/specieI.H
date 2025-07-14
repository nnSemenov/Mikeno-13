/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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

\*---------------------------------------------------------------------------*/

#include "specie.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

inline specie::specie
(
    const word& name,
    const scalar Y,
    const scalar molWeight,
    const scalar Tc,
    const scalar Vc,
    const scalar Pc,
    const scalar omega
)
:
    name_(name),
    Y_(Y),
    molWeight_(molWeight),
    Tc_(Tc),
    Vc_(Vc),
    Pc_(Pc),
    omega_(omega)
{}


inline specie::specie
(
    const scalar Y,
    const scalar molWeight,
    const scalar Tc,
    const scalar Vc,
    const scalar Pc,
    const scalar omega
)
:
    Y_(Y),
    molWeight_(molWeight),
    Tc_(Tc),
    Vc_(Vc),
    Pc_(Pc),
    omega_(omega)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline specie::specie(const word& name, const specie& st)
:
    name_(name),
    Y_(st.Y_),
    molWeight_(st.molWeight_),
    Tc_(st.Tc_),
    Vc_(st.Vc_),
    Pc_(st.Pc_),
    omega_(st.omega_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const word& specie::name() const
{
    return name_;
}


inline scalar specie::W() const
{
    return molWeight_;
}


inline scalar specie::Y() const
{
    return Y_;
}


inline scalar specie::R() const
{
    return RR/molWeight_;
}

inline scalar specie::Tc() const {
    return this->Tc_;
}

inline scalar specie::Zc() const {
    return Pc_*Vc_/(RR*Tc_);
}

inline scalar specie::Pc() const {
    return this->Pc_;
}

inline scalar specie::omega() const {
    return this->omega_;
}

inline scalar specie::Vc() const {
    return this->Vc_;
}

// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline void specie::operator=(const specie& st)
{
    // name_ = st.name_;
    Y_ = st.Y_;
    molWeight_ = st.molWeight_;

    Tc_=st.Tc_;
    Vc_=st.Vc_;
    Pc_=st.Pc_;
    omega_=st.omega_;
}


inline void specie::operator+=(const specie& st)
{
    const scalar sumY = Y_ + st.Y_;
    if (mag(sumY) > small)
    {
        molWeight_ = sumY/(Y_/molWeight_ + st.Y_/st.molWeight_);

        const scalar moleScore0=this->Y_/this->molWeight_;
        const scalar moleScore1=st.Y_/st.molWeight_;
        const scalar X0=moleScore0/(moleScore0+moleScore1);
        const scalar X1=moleScore1/(moleScore0+moleScore1);
        this->Tc_=X0*this->Tc_+X1*st.Tc_;
        this->Vc_=X0*this->Vc_+X1*st.Vc_;
        this->Pc_=X0*this->Pc_+X1*st.Pc_;
        this->omega_=X0*this->omega_+X1*st.omega_;
    }

    Y_ = sumY;
}


inline void specie::operator*=(const scalar s)
{
    Y_ *= s;
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

inline specie operator+(const specie& st1, const specie& st2)
{
    const scalar sumY = max(st1.Y_ + st2.Y_, small);

    if (mag(sumY) > small)
    {
        const scalar moleScore1=st1.Y_/st1.molWeight_;
        const scalar moleScore2=st2.Y_/st2.molWeight_;
        const scalar X1=moleScore1/(moleScore1+moleScore2);
        const scalar X2=moleScore2/(moleScore1+moleScore2);
        return specie
        (
            sumY,
            sumY/(st1.Y_/st1.molWeight_ + st2.Y_/st2.molWeight_),
            X1*st1.Tc_+X2*st2.Tc_,
            X1*st1.Vc_+X2*st2.Vc_,
            X1*st1.Pc_+X2*st2.Pc_,
            X1*st1.omega_+X2*st2.omega_
        );
    }
    else
    {
        return st1;
    }
}


inline specie operator*(const scalar s, const specie& st)
{
    return specie
    (
        s*st.Y_,
        st.molWeight_,
        st.Tc_,
        st.Vc_,
        st.Pc_,
        st.omega_
    );
}


inline specie operator==(const specie& st1, const specie& st2)
{
    scalar diffY = st2.Y_ - st1.Y_;
    if (mag(diffY) < small)
    {
        diffY = small;
    }

    const scalar diffRW =
        st2.Y_/st2.molWeight_ - st1.Y_/st1.molWeight_;

    scalar molWeight = great;
    if (mag(diffRW) > small)
    {
        molWeight = diffY/diffRW;
    }
#warning "Implement some kind of mixing of Tc, Vc, Pc, omega"
    return specie(diffY, molWeight, st1.Tc_, st1.Vc_, st1.Pc_, st1.omega_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
