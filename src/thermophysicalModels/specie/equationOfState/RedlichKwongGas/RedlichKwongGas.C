/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
<<<<<<<< HEAD:src/thermophysicalModels/specie/equationOfState/RedlichKwongGas/RedlichKwongGas.C
    \\  /    A nd           | Copyright (C) 2014-2023 OpenFOAM Foundation
========
    \\  /    A nd           | Copyright (C) 2011-2025 OpenFOAM Foundation
>>>>>>>> upstream/master:src/meshTools/meshSearch/meshSearchBoundBox.C
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

<<<<<<<< HEAD:src/thermophysicalModels/specie/equationOfState/RedlichKwongGas/RedlichKwongGas.C
#include "RedlichKwongGas.H"
#include "IOstreams.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
Foam::RedlichKwongGas<Specie>::RedlichKwongGas
        (
                const word& name,
                const dictionary& dict
        )
        :
        Specie(name, dict)
{
    this->requireRealGasEOS(false);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


template<class Specie>
void Foam::RedlichKwongGas<Specie>::write(Ostream& os) const
{
    Specie::write(os);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class Specie>
Foam::Ostream& Foam::operator<<
        (
                Ostream& os,
                const RedlichKwongGas<Specie>& pg
        )
{
    pg.write(os);
    return os;
}
========
#include "meshSearchBoundBox.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(meshSearchBoundBox, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::meshSearchBoundBox::meshSearchBoundBox(const polyMesh& mesh)
:
    DemandDrivenMeshObject
    <
        polyMesh,
        DeletableMeshObject,
        meshSearchBoundBox
    >(mesh),
    bb_(treeBoundBox(mesh.points()).extend(1e-4))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::meshSearchBoundBox::~meshSearchBoundBox()
{}
>>>>>>>> upstream/master:src/meshTools/meshSearch/meshSearchBoundBox.C


// ************************************************************************* //
