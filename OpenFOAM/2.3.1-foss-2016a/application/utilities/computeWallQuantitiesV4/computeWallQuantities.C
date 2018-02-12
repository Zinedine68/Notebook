/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
     \\/     M anipulation  |
------------------------------------------------------------------------------- License This file is part of OpenFOAM.

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
    averageAlongAxis

Description
    Average field along a chosen axis.

    Assuming that the mesh is periodic in the direction of the axis.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "ReadFields.H"
#include "wallFvPatch.H"
#include "nearWallDist.H"
#include "OFstream.H"

#include "OSspecific.H"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    argList::noParallel();
    argList::addBoolOption("wallModel");
    argList::addBoolOption("noMeanFields");
    timeSelector::addOptions();

#   include "setRootCase.H"
#   include "createTime.H"

    // Get times list
    instantList timeDirs = timeSelector::select0(runTime, args);

#   include "createMesh.H"
#   include "readTransportProperties.H"


    // For each time step read all fields
    forAll(timeDirs, timeI)
    {
        runTime.setTime(timeDirs[timeI], timeI);
        Info << "Computing wall quantities for time " << runTime.timeName() << endl;
        
        volScalarField r
        (
           IOobject
           (
               "r",
               runTime.timeName(),
               mesh,
               IOobject::NO_READ,
               IOobject::AUTO_WRITE
               ),
               mesh,
			   dimensionedScalar("r", dimLength, scalar(0.0))
         );

/*	
	//This block reads a labelListList
	//face is a list of faces and face it self is a list so polyMesh/faces is an example of
	//labelListList

	//labelListIOList proximityCells  // this gives error labelListIOList is not in this scope
	IOList<labelList> proximityCells  // while this class is well recognized
	(
		IOobject
		(
			"proximityCells",
			runTime.time().constant(), 
			mesh,
			IOobject::MUST_READ,
			IOobject::NO_WRITE
		)
	);
	Info << "size : " << proximityCells.size() << endl;
	Info << "size : " << proximityCells[0] << endl;
	Info << "size : " << proximityCells[1] << endl;
*/

	IOList<label> myCells(
    	IOobject(
                 "myCells",
                 runTime.time().constant(),
                 mesh,
                 IOobject::MUST_READ,
                 IOobject::NO_WRITE
            )
     );
        // Get index of patch

        const word w0("Port1");
		const word w1("outlet");
		const word w2("wall");

        /*
        const word w0("movingWall");
		const word w1("fixedWalls");
		const word w2("frontAndBack");
		*/

		label nb_fvPatch = mesh.boundaryMesh().size();

		const label w0PatchID = mesh.boundaryMesh().findPatchID(w0);
		const label w1PatchID = mesh.boundaryMesh().findPatchID(w1);
		const label w2PatchID = mesh.boundaryMesh().findPatchID(w2);

		Info<< "Size of fvBoundryMesh = "
			<< nb_fvPatch << "\n"<< endl;
		Info<< "PatchID for "
			<< w0
			<< " is "
			<< w0PatchID << "\n" << endl;
		Info<< "PatchID for "
			<< w1
			<< " is "
			<< w1PatchID << "\n" << endl;
		Info<< "PatchID for "
			<< w2
			<< " is "
			<< w2PatchID << "\n" << endl;


        // Distance to the wall for the near-wall cells
        volScalarField::GeometricBoundaryField d = nearWallDist(mesh).y();

        const fvPatchList& patches = mesh.boundary();

        fileName writePathRoot("./V3_csv/computeWallQuantities"/runTime.timeName());
        mkDir(writePathRoot);

        // Go through patches
        forAll(patches, patchI)
        {
            const fvPatch& currPatch = patches[patchI];

            if (currPatch.name() == w0)
            {
            	Info << "entering patch " << w0
            			<< " size = " << currPatch.size() << endl;
            	Info << "entering patch.Cf() " << w0
            			<< " size = " << currPatch.Cf().size() << endl;

        		labelList myList;
/*
				// This block works, well... the initialization for a list is nasty
        		labelList lst;
				//wrong answers
				//lst = {1, 2, 3, 4};
				//lst = {label 1, label 4};
				//lst = (label 1, label 2, label 3, label 4); // wrong
				//lst = (1, 2, 3, 4);  // gives warning only, check size of lst => 0. Wrong answser
				label a = 279;
				label b = 289;
				label c = 299;
				lst.append(a);
				lst.append(b);
				lst.append(c);
				Info << "lst size : " << lst.size() << endl;
				forAll(lst, i)
				{
      				Info<< "lst : " << lst[i] << " " <<  currPatch.Cf()[lst[i]].component(vector::Y) << endl;
				}
*/
				forAll(myCells, i)
				{
      				Info<< "myCells : " << myCells[i] << " " << currPatch.Cf()[myCells[i]].component(vector::X) << endl;
				}
        		scalar x,y,z;
        		vector ctr(0, -0.2, 0);

            	forAll(currPatch, faceI)
            	{
            		// this is for internal mesh and uses the global label list
            		// Info << "coordinates : " << mesh.C()[faceI] << endl;

            		// this is for boundary mesh
					// get the labelList of cells satisfying the criteria below
            		if (currPatch.Cf()[faceI].component(vector::Z) < 0.0005
            				&&
						currPatch.Cf()[faceI].component(vector::Z) > 0	)
            		{
                		//Info << "coordinates : " << faceI << " " << currPatch.Cf()[faceI] << endl;
                		myList.append(faceI);
            		}

            		x = currPatch.Cf()[faceI].component(vector::X);
            		y = currPatch.Cf()[faceI].component(vector::Y);
            		z = currPatch.Cf()[faceI].component(vector::Z);

            		r.boundaryField()[patchI][faceI] = mag(ctr - vector(x, y, z));
            	}
            	Info<< "myList = " << myList << endl;

            	mkDir(writePathRoot/currPatch.name());
                OFstream yCoorFile(
                        fileName(writePathRoot/currPatch.name()/"yCoor"));
                OFstream xCoorFile(
                        fileName(writePathRoot/currPatch.name()/"xCoor"));


                forAll(myList, i)
                {
                	Info << "label and coordinates :" << myList[i] << " " << currPatch.Cf()[myList[i]] << endl;
                	yCoorFile << currPatch.Cf()[myList[i]].component(vector::X) <<
                        " " << currPatch.Cf()[myList[i]].component(vector::Y) <<
                        " " << currPatch.Cf()[myList[i]].component(vector::Z) << endl;
                }

                forAll(myCells, i)
                {
                	Info << "label and coordinates :" << myCells[i] << " " << currPatch.Cf()[myCells[i]] << endl;
                	xCoorFile << currPatch.Cf()[myCells[i]].component(vector::X) <<
                        " " << currPatch.Cf()[myCells[i]].component(vector::Y) <<
                        " " << currPatch.Cf()[myCells[i]].component(vector::Z) << endl;
                }

            	/*
            	// if vect is one random point, findCell will return global label
        		vector vect(0.0004 , -2.96525e-21 , 0.004);
        		Info << "point label : " << mesh.findCell(vect) << endl;
        		Info << "coordinates : " << mesh.C()[mesh.findCell(vect)] << endl;
        		*/
        		//Info << "point label : " << currPatch.findCell(vect) << endl;  // doesn't work
            }
    	}
        r.write();

    }
    Info<< "\nEnd\n" << endl;

    return 0;
}


// ************************************************************************* //
