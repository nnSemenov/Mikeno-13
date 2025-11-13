/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
<<<<<<<< HEAD:src/meshTools/meshSearch/meshSearchBoundBox.H
    \\  /    A nd           | Copyright (C) 2011-2025 OpenFOAM Foundation
========
    \\  /    A nd           | Copyright (C) 2019-2025 OpenFOAM Foundation
>>>>>>>> upstream/master:applications/modules/multiphaseEuler/populationBalance/shapeModels/spherical/spherical.H
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
<<<<<<<< HEAD:src/meshTools/meshSearch/meshSearchBoundBox.H
    Foam::meshSearchBoundBox

Description
    Mesh object to hold a bound box for use by mesh search engines

SourceFiles
    meshSearchBoundBox.C

\*---------------------------------------------------------------------------*/

#ifndef meshSearchBoundBox_H
#define meshSearchBoundBox_H

#include "DemandDrivenMeshObject.H"
#include "polyMesh.H"
#include "treeBoundBox.H"
========
    Foam::populationBalance::shapeModels::spherical

Description
    Spherical shape model

SourceFiles
    spherical.C

\*---------------------------------------------------------------------------*/

#ifndef spherical_H
#define spherical_H

#include "shapeModel.H"
>>>>>>>> upstream/master:applications/modules/multiphaseEuler/populationBalance/shapeModels/spherical/spherical.H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
<<<<<<<< HEAD:src/meshTools/meshSearch/meshSearchBoundBox.H

// Forward declaration of classes
class treeBoundBox;

/*---------------------------------------------------------------------------*\
                         Class meshSearchBoundBox Declaration
\*---------------------------------------------------------------------------*/

class meshSearchBoundBox
:
    public DemandDrivenMeshObject
    <
        polyMesh,
        DeletableMeshObject,
        meshSearchBoundBox
    >
========
namespace populationBalance
{
namespace shapeModels
>>>>>>>> upstream/master:applications/modules/multiphaseEuler/populationBalance/shapeModels/spherical/spherical.H
{
    // Private Data

<<<<<<<< HEAD:src/meshTools/meshSearch/meshSearchBoundBox.H
        //- Bound box
        const treeBoundBox bb_;

========
/*---------------------------------------------------------------------------*\
                          Class spherical Declaration
\*---------------------------------------------------------------------------*/
>>>>>>>> upstream/master:applications/modules/multiphaseEuler/populationBalance/shapeModels/spherical/spherical.H

class spherical
:
    public shapeModel
{
public:

<<<<<<<< HEAD:src/meshTools/meshSearch/meshSearchBoundBox.H
    //- Run-time type information
    TypeName("meshSearchBoundBox");
========
    //- Runtime type information
    TypeName("spherical");
>>>>>>>> upstream/master:applications/modules/multiphaseEuler/populationBalance/shapeModels/spherical/spherical.H


    // Constructors

<<<<<<<< HEAD:src/meshTools/meshSearch/meshSearchBoundBox.H
        //- Construct from mesh
        meshSearchBoundBox(const polyMesh& mesh);

        //- Disallow default bitwise copy construction
        meshSearchBoundBox(const meshSearchBoundBox&) = delete;


    //- Destructor
    virtual ~meshSearchBoundBox();
========
        //- Construct from a dictionary
        spherical
        (
            const dictionary& dict,
            const populationBalanceModel& popBal
        );


    //- Destructor
    virtual ~spherical();
>>>>>>>> upstream/master:applications/modules/multiphaseEuler/populationBalance/shapeModels/spherical/spherical.H


    // Member Functions

<<<<<<<< HEAD:src/meshTools/meshSearch/meshSearchBoundBox.H
        // Access

            //- Access the bound box
            inline const treeBoundBox& bb() const
            {
                return bb_;
            }


    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const meshSearchBoundBox&) = delete;
========
        //- Return the representative surface area of a group
        virtual tmp<volScalarField> a(const label i) const;

        //- Return the representative diameter of a group
        virtual tmp<volScalarField> d(const label i) const;
>>>>>>>> upstream/master:applications/modules/multiphaseEuler/populationBalance/shapeModels/spherical/spherical.H
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace shapeModels
} // End namespace populationBalance
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
