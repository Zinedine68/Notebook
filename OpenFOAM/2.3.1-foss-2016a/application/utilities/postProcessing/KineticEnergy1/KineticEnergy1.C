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
    Modified from Lambda2

Description
    The -noWrite option has no meaning.

Usage
	KineticEnergy -time '99950'
	mpirun -n 4 KineticEnergy -time '99950' -parallel

\*---------------------------------------------------------------------------*/

#include "calc.H"
#include "fvc.H"

//#include "OFstream.H" // Actually this is more than needed : ofstream
#include <fstream>
using std::ofstream;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

/*
 *  Here remind you that you are in the namespace Foam by 
 *
 *  Foam::calc(... ... ...)
 *
 *  Evidence : in calc.H function calc is { } by namespace Foam
 */
void Foam::calc(const argList& args, const Time& runTime, const fvMesh& mesh)
{
    IOobject Uheader
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ
    );

	/*
    volScalarField uniformF
    (
        IOobject
        (
                "uniformF",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedScalar("uniformF", dimless, 1.0)
    );

	//uniformF.write();
	//Info << "uniformF :" << uniformF << endl;
	*/

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

		Info<< "    Summing up : gSum(KE) = "<< gSum(KE) << endl;
		Info<< "    Summing up :  Sum(KE) = "<< sum(KE) << endl;

		//DimensionedScalar DwaKE = KE.weightedAverage(mesh.V());
		dimensionedScalar DwaKE = KE.weightedAverage(mesh.V());
		Info<< "    DwaKE : " << DwaKE << endl;


    volScalarField DwaKEF
    (
        IOobject
        (
                "DwaKEF",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
        ),
        mesh,
        DwaKE
    );
    //DwaKEF.write();
	    
	    volScalarField c = KE-DwaKEF;
	    //Info<< "this should be zero : " << (KE-DwaKEF).weightedAverage(mesh.V());
	    Info<< "    this should be zero : " << c.weightedAverage(mesh.V());
	    Info<< "    this should note be zero : " << c.average();

		scalar waKE = DwaKE.value();
		Info<< "    Summing up : weighted average of KE = "
				<<  waKE  << nl
				/*
				<< "WeightedAverage : here the weight is cellVolume/TotalVolume" << nl
				<< "Note that this is verified by paraview - Filter - intergate " << nl
				<< "which is a volumic integration. Divide the paraview calculation " << nl
				<< "by volume, you will get the same as here" << endl;
				*/
				<< endl;

		const scalar totalVol = gSum(mesh.V());
		Info<< "    totalVol              = "<< totalVol << endl;

		fileName writePathRoot("./postProcessing");
    	mkDir(writePathRoot/"fieldStatistics");

		ofstream KineticEnergy(fileName(writePathRoot/"fieldStatistics"/"KineticEnergy").c_str(), ios_base::app);
		if (Pstream::master())
		{
			//std::cout << runTime.timeName().c_str() << " " << waKE << "\n" << std::endl;
    		KineticEnergy << runTime.timeName().c_str() << " " << waKE << std::endl; // This is the right and safest way to do

    		//KineticEnergy << runTime.timeName().c_str() << " " << waKE << endl;  // same as Foam::endl : no error in compilation but "endl" will not work as expected.
    		//KineticEnergy << runTime.timeName().c_str() << " " << waKE << Foam::endl;  
		}
    }
    else
    {
        Info<< "    No U" << endl;
    }

	Info<< "Using appending mode in writting data, be sure that the old data is erased before executing!" << endl;

    Info<< "\nEnd\n" << endl;
}


// ************************************************************************* //
