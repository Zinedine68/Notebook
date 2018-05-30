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
    Calculates and writes the vorticity of velocity field U.

    The -noWrite option just outputs the max/min values without writing
    the field.

\*---------------------------------------------------------------------------*/

#include "calc.H"
#include "fvc.H"

#include "OFstream.H"

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

        Info<< "    Calculating vorticity" << endl;
        volVectorField vorticity
        (
            IOobject
            (
                "vorticity",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ
            ),
            fvc::curl(U)
        );

        volScalarField magVorticity
        (
            IOobject
            (
                "magVorticity",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ
            ),
            mag(vorticity)
        );

    //IOList<labelList> prox  // while this class is well recognized
    IOList<label> prox  // while this class is well recognized
    (
        IOobject
        (
            "proximityCells",
            runTime.time().constant(),
            mesh,
            //IOobject::MUST_READ,
            IOobject::NO_READ,
            //IOobject::NO_WRITE
            IOobject::AUTO_WRITE
        )
    );

	List<label> prox0(8);
    prox0[0] = 7.0;
    prox0[1] = 9.0;
    prox0[2] = 1.0;
    prox0[3] = 2.1;
    prox0[4] = 4.0;
    prox0[5] = 7.0;
    prox0[6] = 4.0;
    prox0[7] = 0.0;
	IOList<label> prox1
	(
		IOobject
	   	(
			"prox1",
		    runTime.time().constant(),
			mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
		),
		prox0
	);

	List<labelList> proxListE(1);
	proxListE[0] = prox0;
	IOList<labelList> proxList
	(
		IOobject
	   	(
			"proxList",
		    runTime.time().constant(),
			mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
		),
		proxListE
	);

	//Info << "prox : " << prox[0] << endl;
	//
    Info<< "Writing " << prox.name() << " to " << prox.objectPath() << endl;

    OFstream os(prox.objectPath());
    OFstream os1(prox1.objectPath());
    OFstream osList(proxList.objectPath());

	prox.writeHeader(os);
	prox1.writeHeader(os1);
	proxList.writeHeader(osList);

	os1 << prox1;
	osList << proxList;
	//prox[0] = 1;
	//prox.write();

        Info<< "vorticity max/min : "
            << max(magVorticity).value() << " "
            << min(magVorticity).value() << endl;

        if (writeResults)
        {
            vorticity.write();
            magVorticity.write();
        }
    }
    else
    {
        Info<< "    No U" << endl;
    }

    Info<< "\nEnd\n" << endl;
}


// ************************************************************************* //
