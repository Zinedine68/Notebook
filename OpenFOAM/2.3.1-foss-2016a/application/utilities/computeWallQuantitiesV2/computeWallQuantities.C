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
        
        // Load/create fields




        word UName = "UMean";
        word pName = "pMean";
        word nuSgsName = "nuSgsMean";

        if(args.optionFound("noMeanFields"))
        {
            UName = "U";
            pName = "p";
            nuSgsName = "nuSgs";
        }
            
        

        Info<< "Reading field "<< UName << endl;

        volVectorField UMean
        (
           IOobject
           (
               UName,
               runTime.timeName(),
               mesh,
               IOobject::MUST_READ,
               IOobject::NO_WRITE
               ),
               mesh
         );

        Info<< "Reading field " << pName << endl;

        volScalarField pMean
        (
           IOobject
           (
               pName,
               runTime.timeName(),
               mesh,
               IOobject::MUST_READ,
               IOobject::NO_WRITE
               ),
               mesh
         );

        // Convert laminar visocity to a GeometricField
        volScalarField nuLam 
        (
            IOobject
            (
                "nuLam",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            mesh,
            dimensionedScalar("nuLam", nu.dimensions(), nu.value())
        );

        volScalarField nuEff(nuLam);

        // Check if we need to consider nuSgsMean at the wall
        if(args.optionFound("wallModel"))
        {
            Info<< "Reading field " << nuSgsName << endl;

            volScalarField nuSgsMean 
            (
            IOobject
            (
                nuSgsName,
                runTime.timeName(),
                mesh,
                IOobject::MUST_READ,
                IOobject::NO_WRITE
                ),
                mesh
            );

            nuEff = nuLam + nuSgsMean;
        }
        else
        {    
            nuEff = nuLam;
        }

        volScalarField yPlus
        (
            IOobject
            (
                "yPlus",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            mesh,
            dimensionedScalar("yPlus", dimless, 0.0)
        );

        volScalarField uTau
        (
            IOobject
            (
                "uTau",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            mesh,
            dimensionedScalar("uTau", UMean.dimensions(), 0.0)
        );

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
			   //dimensionedVector("coor", dimLength, (0.0 , 0.0 , 0.0)) // this doesn't work
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
		// call size() of mother class fvPatchList
		label nb_fvPatch = mesh.boundaryMesh().size();
		//
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


        // Grab the distance to the wall for the near-wall cells
        volScalarField::GeometricBoundaryField d = nearWallDist(mesh).y();



        const fvPatchList& patches = mesh.boundary();

        fileName writePathRoot("./postProcessing/computeWallQuantities"/runTime.timeName());
        mkDir(writePathRoot);

        // Go through wall-patches and compute the quantities
        forAll(patches, patchI)
        {
            const fvPatch& currPatch = patches[patchI];

            if (currPatch.name() == w0)
            {
            	Info << "entering patch " << w0
            			<< " size = " << currPatch.size() << endl;

        		labelList myList;
        		scalar x,y,z;
        		vector ctr(0, -0.2, 0);
        		Info << "magnitude : " << mag(ctr) << endl;

            	forAll(currPatch, faceI)
            	{
            		// this is for internal mesh and uses the global label list
            		//Info << "coordinates : " << mesh.C()[faceI] << endl;
            		// this is for boundary mesh
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

                forAll(myList, i)
                {
                	Info << "label and coordinates :" << myList[i] << " " << currPatch.Cf()[myList[i]] << endl;
                	yCoorFile << currPatch.Cf()[myList[i]].component(vector::X) <<
                        " " << currPatch.Cf()[myList[i]].component(vector::Y) <<
                        " " << currPatch.Cf()[myList[i]].component(vector::Z) << endl;
                }

                //coor.boundaryField()[patchI]=currPatch.Cf();

            	/*
            	// if vect is one random point, findCell will return global label
        		vector vect(0.0004 , -2.96525e-21 , 0.004);
        		Info << "point label : " << mesh.findCell(vect) << endl;
        		Info << "coordinates : " << mesh.C()[mesh.findCell(vect)] << endl;
        		*/
        		//Info << "point label : " << currPatch.findCell(vect) << endl;  // doesn't work
            }

            if (isA<wallFvPatch>(currPatch))
            {
                Info << "Calculating for patch " << currPatch.name() << endl;

                uTau.boundaryField()[patchI] = 
                    sqrt(
                         nuEff.boundaryField()[patchI]
                        *mag(UMean.boundaryField()[patchI].snGrad())
                        );

                yPlus.boundaryField()[patchI] = d[patchI]*
                    uTau.boundaryField()[patchI]/nuLam[patchI];


                mkDir(writePathRoot/currPatch.name());

                OFstream yPlusFile(
                        fileName(writePathRoot/currPatch.name()/"yPlus"));

                OFstream uTauFile(
                        fileName(writePathRoot/currPatch.name()/"uTau"));

                OFstream pMeanFile(
                        fileName(writePathRoot/currPatch.name()/"pMean"));

                OFstream distFile(
                        fileName(writePathRoot/currPatch.name()/"dist"));
                
                forAll(currPatch, faceI)
                {
                    yPlusFile << currPatch.Cf()[faceI].component(vector::X) <<
                        " " << currPatch.Cf()[faceI].component(vector::Y) <<
                        " " << currPatch.Cf()[faceI].component(vector::Z) <<
                        " " << yPlus.boundaryField()[patchI][faceI] << endl;

                    uTauFile << currPatch.Cf()[faceI].component(vector::X) <<
                        " " << currPatch.Cf()[faceI].component(vector::Y) <<
                        " " << currPatch.Cf()[faceI].component(vector::Z) <<
                        " " << uTau.boundaryField()[patchI][faceI] << endl;

                    pMeanFile << currPatch.Cf()[faceI].component(vector::X) <<
                        " " << currPatch.Cf()[faceI].component(vector::Y) <<
                        " " << currPatch.Cf()[faceI].component(vector::Z) <<
                        " " << pMean.boundaryField()[patchI][faceI] << endl;

                    distFile << currPatch.Cf()[faceI].component(vector::X) <<
                        " " << currPatch.Cf()[faceI].component(vector::Y) <<
                        " " << currPatch.Cf()[faceI].component(vector::Z) <<
                        " " << d[patchI][faceI] << endl;
                    
                }

            }

    }
        r.write();

    }

    Info<< "\nEnd\n" << endl;

    return 0;
}


// ************************************************************************* //
