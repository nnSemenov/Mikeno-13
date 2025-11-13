/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
<<<<<<<< HEAD:src/meshTools/meshSearch/meshSearchBoundBox.C
    \\  /    A nd           | Copyright (C) 2011-2025 OpenFOAM Foundation
========
    \\  /    A nd           | Copyright (C) 2025 OpenFOAM Foundation
>>>>>>>> upstream/master:src/finiteVolume/fields/fvsPatchFields/derived/zeroFixedValue/zeroFixedValueFvsPatchFields.C
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

<<<<<<<< HEAD:src/meshTools/meshSearch/meshSearchBoundBox.C
#include "meshSearchBoundBox.H"
========
#include "zeroFixedValueFvsPatchFields.H"
#include "surfaceFields.H"
#include "addToRunTimeSelectionTable.H"
>>>>>>>> upstream/master:src/finiteVolume/fields/fvsPatchFields/derived/zeroFixedValue/zeroFixedValueFvsPatchFields.C

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
<<<<<<<< HEAD:src/meshTools/meshSearch/meshSearchBoundBox.C
    defineTypeNameAndDebug(meshSearchBoundBox, 0);
}
========
>>>>>>>> upstream/master:src/finiteVolume/fields/fvsPatchFields/derived/zeroFixedValue/zeroFixedValueFvsPatchFields.C

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

makeFvsPatchFields(zeroFixedValue);

<<<<<<<< HEAD:src/meshTools/meshSearch/meshSearchBoundBox.C
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
========
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
>>>>>>>> upstream/master:src/finiteVolume/fields/fvsPatchFields/derived/zeroFixedValue/zeroFixedValueFvsPatchFields.C

} // End namespace Foam

// ************************************************************************* //
