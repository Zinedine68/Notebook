/*---------------------------------------------------------------------------* \
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
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

Application
    vorticity

Description
    Calculates and writes the U^2 and U^3 of velocity field U.

    The -noWrite option just outputs the max/min values without writing
    the field.

\*---------------------------------------------------------------------------*/

#include "calc.H"
#include "fvc.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

void Foam::calc(const argList& args, const Time& runTime, const fvMesh& mesh)
{
    bool writeResults = !args.optionFound("noWrite");

    IOobject Uheader
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ
    );

    if (Uheader.headerOk())
    {
        Info<< "    Reading U" << endl;
        volVectorField U(Uheader, mesh);

        Info<< "    Calculating U^2" << endl;
        volVectorField U2 
        (
            IOobject
            (
                "U2",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ
            ),
            mesh,
			dimensionedVector("U2",dimensionSet(0, 2, -2, 0, 0, 0, 0),vector::zero)
        );

        Info<< "    Calculating U^3" << endl;
        volVectorField U3 
        (
            IOobject
            (
                "U3",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ
            ),
			mesh,
			dimensionedVector("U3",dimensionSet(0, 3, -3, 0, 0, 0, 0),vector::zero)
        );

		/* only the internal */
		//U2.internalField().replace(vector::Z, Ux.internalField());
		/* include the boundary */
/*		U2.replace(vector::X, U.component(vector::X)*U.component(vector::X));
		U2.replace(vector::Y, U.component(vector::Y)*U.component(vector::Y));
		U2.replace(vector::Z, U.component(vector::Z)*U.component(vector::Z));
*/
		U2.replace(vector::X, pow(U.component(vector::X), 2));
		U2.replace(vector::Y, pow(U.component(vector::Y), 2));
		U2.replace(vector::Z, pow(U.component(vector::Z), 2));

		U3.replace(vector::X, pow(U.component(vector::X), 3));
		U3.replace(vector::Y, pow(U.component(vector::Y), 3));
		U3.replace(vector::Z, pow(U.component(vector::Z), 3));
/*
        Info<< "vorticity max/min : "
            << max(magVorticity).value() << " "
            << min(magVorticity).value() << endl;
*/
        if (writeResults)
        {
//            vorticity.write();
//            magVorticity.write();
            U2.write();
            U3.write();
        }
    }
    else
    {
        Info<< "    No U" << endl;
    }

    Info<< "\nEnd\n" << endl;
}


// ************************************************************************* //
