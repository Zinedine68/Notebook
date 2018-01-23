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
    Calculates and writes the skewness and flatness of velocity field U.

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
        "UMean",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ
    );

    IOobject U2_for_Mean
    (
        "U2Mean",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ
    );

    IOobject U3_for_Mean
    (
        "U3Mean",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ
    );

    if (Uheader.headerOk())
    {
        Info<< "    Reading UMean" << endl;
        volVectorField UMean(Uheader, mesh);
        Info<< "    Reading U2Mean" << endl;
        volVectorField U2Mean(U2_for_Mean, mesh);
        Info<< "    Reading U3Mean" << endl;
        volVectorField U3Mean(U3_for_Mean, mesh);

        Info<< "    Calculating M2" << endl;
        volVectorField M2 
        (
            IOobject
            (
                "M2",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
			mesh,
			dimensionedVector("M2",dimensionSet(0, 2, -2, 0, 0, 0, 0),vector(0, 0, 0))
        );

		M2.replace(vector::X, U2Mean.component(vector::X) 
							- pow(UMean.component(vector::X), 2));
		M2.replace(vector::Y, U2Mean.component(vector::Y) 
							- pow(UMean.component(vector::Y), 2));
		M2.replace(vector::Z, U2Mean.component(vector::Z) 
							- pow(UMean.component(vector::Z), 2));

        Info<< "    Calculating M3" << endl;
        volVectorField M3 
        (
            IOobject
            (
                "M3",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ
            ),
			mesh,
			dimensionedVector("M3",dimensionSet(0, 3, -3, 0, 0, 0, 0),vector(0, 0, 0))
        );

		M3.replace(vector::X, U3Mean.component(vector::X) 
							- 3.0
							  * UMean.component(vector::X)
							  * U2Mean.component(vector::X)
							+ 2.0
							  * U3Mean.component(vector::X)
							);
		M3.replace(vector::Y, U3Mean.component(vector::Y) 
							- 3.0
							  * UMean.component(vector::Y)
							  * U2Mean.component(vector::Y)
							+ 2.0
							  * U3Mean.component(vector::Y)
							);
		M3.replace(vector::Z, U3Mean.component(vector::Z) 
							- 3.0
							  * UMean.component(vector::Z)
							  * U2Mean.component(vector::Z)
							+ 2.0
							  * U3Mean.component(vector::Z)
							);

		// non-dimensionize the skewness factor
		// floating point exception !!!
		// for the first and last element which are both on the wall
		//
		/*
		M3.replace(vector::X, M3.component(vector::X)
								/
							  pow(M2.component(vector::X),3.0/2.0));
		M3.replace(vector::Y, M3.component(vector::Y)
								/
							  pow(M2.component(vector::Y),3.0/2.0));
		M3.replace(vector::Z, M3.component(vector::Z)
								/
							  pow(M2.component(vector::Z),3.0/2.0));
		*/

		/* only the internal */
		//U2.internalField().replace(vector::Z, Ux.internalField());
		/* include the boundary */
/*		U2.replace(vector::X, U.component(vector::X)*U.component(vector::X));
		U2.replace(vector::Y, U.component(vector::Y)*U.component(vector::Y));
		U2.replace(vector::Z, U.component(vector::Z)*U.component(vector::Z));
*/
/*
		U2.replace(vector::X, pow(U.component(vector::X), 2));
		U2.replace(vector::Y, pow(U.component(vector::Y), 2));
		U2.replace(vector::Z, pow(U.component(vector::Z), 2));

		U3.replace(vector::X, pow(U.component(vector::X), 3));
		U3.replace(vector::Y, pow(U.component(vector::Y), 3));
		U3.replace(vector::Z, pow(U.component(vector::Z), 3));
*/
/*
        Info<< "vorticity max/min : "
            << max(magVorticity).value() << " "
            << min(magVorticity).value() << endl;
*/
        if (writeResults)
        {
//            vorticity.write();
//            magVorticity.write();
			M2.write();
			M3.write();
        }
    }
    else
    {
        Info<< "    No U" << endl;
    }

    Info<< "\nEnd\n" << endl;
}


// ************************************************************************* //
