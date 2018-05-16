/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 1991-2009 OpenCFD Ltd.
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Application
    foamTimeAverage

Eelco van Vliet

Version: 
very first piece of ugly c++ code, but it works!

Description
    Calculates the time average  of the specified scalar field over the specified time range.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "argList.H"
#include "timeSelector.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Main program:

int main(int argc, char *argv[])
{

    Foam::timeSelector::addOptions();
    Foam::argList::validArgs.append("fieldName");

    // the order of the calls below is important!

    // defines the first directory
#   include "setRootCase.H"
    // defines time stuff
#   include "createTime.H"

    // get filename from command line
    word fieldName(args.additionalArgs()[0]);

    // create list of time steps based on the -time argument
    instantList timeDirs = timeSelector::select0(runTime, args);
	Info<< "timeDirs : " << timeDirs << endl;
	//Info<< "timeDirs[-1] : " << timeDirs[-1] << endl;
	//Info<< "size : " << timeDirs.size() << endl;
	//Info<< "timeDirs[-1] : " << timeDirs[timeDirs.size()-1] << endl;

    // set the runTime at the first time step of the given range
    runTime.setTime(timeDirs[0], 0);

    // now: create mesh based on the first time step of the given range 
#   include "createMesh.H"


    // read first the field into a dummy variable, otherwise the write
    // statement at the bottom used fieldName to over write the original field.
    // How can I used change the filename instead of this trick? 
    Info<< "    Create var field" << nl<<endl;
    volScalarField dummy
    (
     IOobject
     (
        fieldName,
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ
      ),
     mesh
    );

    
    // create the new file name with the _var extension
    const word EXT_var = "_var";
    const word varFieldName=fieldName+EXT_var;

    // create the field with the varFieldName based on the dummy so that all
    // the properties are the same. Probably can be done much more efficient
    volScalarField var
    (
     IOobject
     (
        varFieldName,
        runTime.timeName(),
        mesh,
        IOobject::NO_READ
      ),
     dummy
    );
	
	// read meanField
	/*
	Info<< "MAKE SURE to read the right mean field in constant/meanField" << endl;
	volScalarField meanField
	(
        IOobject
		(
             "U_mean",
             runTime.time().constant(),
             mesh,
             IOobject::MUST_READ,
             IOobject::NO_WRITE
        )
     );
	 */

     IOobject PMeanHeader
	 (
         "p_mean",
         runTime.time().constant(),
         mesh,
         IOobject::MUST_READ,
         IOobject::NO_WRITE
     );

	 if(PMeanHeader.headerOk())
	 {
		Info<< "MAKE SURE to read the right mean field in constant/meanField" << endl;
		volScalarField meanField(PMeanHeader, mesh);
	 

    // and now initialise at zero. Much better would be to do this right away. 
    // How can that be done?
    var*=0;

    // start the counter out 0;
    int nfield=0;

    // loop over the time directories
    forAll(timeDirs, timeI)
    {
        // set to the current time directory 
        runTime.setTime(timeDirs[timeI], timeI);

		// print all timedir
		Info<< "all time dirs: " << timeDirs << endl;
        // give some information
        Info<< "timeI: "<< timeI<< " Time = " << runTime.timeName() << endl;

        // read the header field 'fieldName'
        IOobject fieldHeader
        (
            fieldName,
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ
        );

        // Check field exists
        if (fieldHeader.headerOk())
        {
            // the mesh exists, read the data
            mesh.readUpdate();

            if (fieldHeader.headerClassName() == "volScalarField")
            {
               // the data is volScalar data -> add the field to the var
               Info<< "    Reading volScalarField " << nfield << " " << fieldName << endl;
               volScalarField field(fieldHeader, mesh);
               var+= sqr(field-meanField);
               nfield++;
            }
            else
            {
                FatalError
                    << "Only possible to average volScalarFields "
                    << nl << exit(FatalError);
            }
        }
        else
        {
            Info<< "    No field " << fieldName << endl;
        }

        Info<< endl;
    }


    // devide by the number of added fields
    if(nfield>0){
      Info<< "number of fields added: "<< nfield << endl;
      var/=nfield;
    }

	} // otherwise the scope of meanField will not cover

    Info<< "writing to file "  << endl;
    var.write();

    Info<< "End\n" << endl;

    return 0;
}

// ************************************************************************* //
