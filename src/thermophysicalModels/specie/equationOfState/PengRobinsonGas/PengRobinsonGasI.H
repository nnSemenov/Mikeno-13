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

\*---------------------------------------------------------------------------*/

#include "PengRobinsonGas.H"
#include "mathematicalConstants.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
inline Foam::PengRobinsonGas<Specie>::PengRobinsonGas
(
    const Specie& sp
)
:
    Specie(sp)
{
    this->requireRealGasEOS(true);
}


template<class Specie>
inline Foam::PengRobinsonGas<Specie>::PengRobinsonGas
(
    const word& name,
    const PengRobinsonGas& pg
)
:
    Specie(name, pg)
{
    pg.requireRealGasEOS(true);
    this->requireRealGasEOS(true);
}


template<class Specie>
inline Foam::autoPtr<Foam::PengRobinsonGas <Specie>>
Foam::PengRobinsonGas<Specie>::clone() const
{
    return autoPtr<PengRobinsonGas<Specie>>
    (
        new PengRobinsonGas<Specie>(*this)
    );
}



// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Specie>
inline void Foam::PengRobinsonGas<Specie>::operator+=
(
    const PengRobinsonGas<Specie>& pg
)
{
//    scalar X1 = this->Y()/this->W();
    Specie::operator+=(pg);

//    if (mag(this->Y()) > small)
//    {
//        X1 *= this->W()/this->Y();
//        const scalar X2 = this->W()*pg.Y()/(pg.W()*this->Y());
//
////        Tc_ = X1*Tc_ + X2*pg.Tc_;
////        Vc_ = X1*Vc_ + X2*pg.Vc_;
////        Zc_ = X1*Zc_ + X2*pg.Zc_;
////        Pc_ = RR*Zc_*Tc_/Vc_;
////        omega_ = X1*omega_ + X2*pg.omega_;
//    }
}


template<class Specie>
inline void Foam::PengRobinsonGas<Specie>::operator*=(const scalar s)
{
     Specie::operator*=(s);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //


template<class Specie>
Foam::PengRobinsonGas<Specie> Foam::operator+
(
    const PengRobinsonGas<Specie>& pg1,
    const PengRobinsonGas<Specie>& pg2
)
{
    Specie sp
    (
        static_cast<const Specie&>(pg1)
      + static_cast<const Specie&>(pg2)
    );

    if (mag(sp.Y()) < small)
    {
        return PengRobinsonGas<Specie>
        (
            sp
        );
    }
    else
    {
        const scalar X1 = sp.W()*pg1.Y()/(pg1.W()*sp.Y());
        const scalar X2 = sp.W()*pg2.Y()/(pg2.W()*sp.Y());

//        const scalar Tc = X1*pg1.Tc_ + X2*pg2.Tc_;
//        const scalar Vc = X1*pg1.Vc_ + X2*pg2.Vc_;
//        const scalar Zc = X1*pg1.Zc_ + X2*pg2.Zc_;

        return PengRobinsonGas<Specie>
        (
            sp
        );
    }
}


template<class Specie>
Foam::PengRobinsonGas<Specie> Foam::operator*
(
    const scalar s,
    const PengRobinsonGas<Specie>& pg
)
{
    return PengRobinsonGas<Specie>
    (
        s*static_cast<const Specie&>(pg)
    );
}


template<class Specie>
Foam::PengRobinsonGas<Specie> Foam::operator==
(
    const PengRobinsonGas<Specie>& pg1,
    const PengRobinsonGas<Specie>& pg2
)
{
    return PengRobinsonGas<Specie>
    (
        static_cast<const Specie&>(pg1) == static_cast<const Specie&>(pg2)
    );
}


// ************************************************************************* //
