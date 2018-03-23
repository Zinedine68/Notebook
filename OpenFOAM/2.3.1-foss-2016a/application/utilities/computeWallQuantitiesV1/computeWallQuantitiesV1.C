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
               IOobject::AUTO_WRITE
               ),
               mesh
         );

		/*
        Info<< "Reading field " << pName << endl;

        volScalarField pMean
        (
           IOobject
           (
               pName,
               runTime.timeName(),
               mesh,
               IOobject::NO_READ,
               IOobject::AUTO_WRITE
               ),
               mesh
         );
		 */

        // Convert laminar visocity to a GeometricField
        volScalarField nuLam 
        (
            IOobject
            (
                "nuLam",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
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
                IOobject::AUTO_WRITE
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
                IOobject::AUTO_WRITE
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
                IOobject::AUTO_WRITE
            ),
            mesh,
            dimensionedScalar("uTau", UMean.dimensions(), 0.0)
        );

        volScalarField dist
        (
           IOobject
           (
               "dist",
               runTime.timeName(),
               mesh,
               IOobject::NO_READ,
               IOobject::AUTO_WRITE
               ),
               mesh,
			   dimensionedScalar("dist", dimLength, 0.0)
         );



        // Grab the distance to the wall for the near-wall cells
        volScalarField::GeometricBoundaryField d = nearWallDist(mesh).y();
		dist.boundaryField() = nearWallDist(mesh).y();



		const fvPatchList& patches = mesh.boundary();

		fileName writePathRoot("./postProcessing/computeWallQuantities"/runTime.timeName());
		mkDir(writePathRoot);

        // Go through wall-patches and compute the quantities
		forAll(patches, patchI)
		{
		    const fvPatch& currPatch = patches[patchI];

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

				/*
                OFstream pMeanFile(
                        fileName(writePathRoot/currPatch.name()/"pMean"));
				*/

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
/*
		            pMeanFile << currPatch.Cf()[faceI].component(vector::X) <<
		                " " << currPatch.Cf()[faceI].component(vector::Y) <<
                        " " << currPatch.Cf()[faceI].component(vector::Z) <<
		                " " << pMean.boundaryField()[patchI][faceI] << endl;
*/
		            distFile << currPatch.Cf()[faceI].component(vector::X) <<
		                " " << currPatch.Cf()[faceI].component(vector::Y) <<
                        " " << currPatch.Cf()[faceI].component(vector::Z) <<
		                " " << d[patchI][faceI] << endl;
		            
		        }

			    yPlus.write();
				uTau.write();
				//pMean.write();
				//d.write();    // this cannot write
				dist.write();   

				Info << "nu = " << nu << endl;
				Info << "nuLam = " << nuLam << endl;
				Info << "uTau max/min : "
						//<< max(uTau).value() << " "
						//<< min(uTau).value() << endl;
						<< max(uTau.boundaryField()) << " "
						<< min(uTau.boundaryField()) << endl;//" "
						//<< mean(uTau.boundaryField()) << endl;
		                                                                                                                       }
		 }

    }

    Info<< "\nEnd\n" << endl;

    return 0;
}


// ************************************************************************* //
