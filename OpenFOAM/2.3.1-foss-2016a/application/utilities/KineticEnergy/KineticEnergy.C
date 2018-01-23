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
    Lambda2

Description
    Calculates and writes the second largest eigenvalue of the sum of the
    square of the symmetrical and anti-symmetrical parts of the velocity
    gradient tensor.

    The -noWrite option has no meaning.

\*---------------------------------------------------------------------------*/

#include "calc.H"
#include "fvc.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

void Foam::calc(const argList& args, const Time& runTime, const fvMesh& mesh)
{
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

        volScalarField KE
        (
            IOobject
            (
                "KE",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
			0.5 * U & U
        );

        Info<< "    Writing -Kinetic Energy : KE " << endl;
        KE.write();

		scalar TKE = gSum(KE);
		Info<< "    Summing up : gSum(KE) = "<< TKE << endl;
		Info<< "    Summing up :  Sum(KE) = "<< sum(KE) << endl;

		//volScalarField k = KE * mesh.V();
		//scalar TKE1 = gSum(k);
		//volScalarField TKE1 = sum(KE * mesh.V())/sum(mesh.V());
		//volScalarField TKE1 = sum(KE * KE)/sum(mesh.V());
		//Info<< "    Summing up : gSum(KE * mesh.V()) = "<< TKE1 << endl;
		Info<< "    Summing up : weighted average of KE = "
				<< KE.weightedAverage(mesh.V()) 
				<< "Note that this is verified by paraview - Filter - intergate "
				<< "which is a volumic integration. Divide the paraview calculation "
				<< "by volume, you will get the same as here" << endl;

		const scalar totalVol = gSum(mesh.V());
		Info<< "    totalVol              = "<< totalVol << endl;
		//Info<< "    totalVol              = "<< one.weightedAverage(mesh.V()) << endl;
    }
    else
    {
        Info<< "    No U" << endl;
    }

    Info<< "\nEnd\n" << endl;
}


// ************************************************************************* //
