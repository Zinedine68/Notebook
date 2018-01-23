/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2013 OpenFOAM Foundation
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
    icoFoam

Description
    Transient solver for incompressible, laminar flow of Newtonian fluids.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "setRootCase.H"

    #include "createTime.H"
    #include "createMesh.H"
    #include "createFields.H"
    #include "initContinuityErrs.H"

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nStarting time loop\n" << endl;

    while (runTime.loop())
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;

        #include "readPISOControls.H"
        #include "CourantNo.H"


        fvVectorMatrix UEqn
        (
            fvm::ddt(U)
          + fvm::div(phi, U)
          - fvm::laplacian(nu, U)
        );

        solve(UEqn == -fvc::grad(p));

        // --- PISO loop

        for (int corr=0; corr<nCorr; corr++)
        {
            volScalarField rAU(1.0/UEqn.A());

            volVectorField HbyA("HbyA", U);
            HbyA = rAU*UEqn.H();
            surfaceScalarField phiHbyA
            (
                "phiHbyA",
                (fvc::interpolate(HbyA) & mesh.Sf())
              + fvc::interpolate(rAU)*fvc::ddtCorr(U, phi)
            );

            adjustPhi(phiHbyA, U, p);

            for (int nonOrth=0; nonOrth<=nNonOrthCorr; nonOrth++)
            {
                fvScalarMatrix pEqn
                (
                    fvm::laplacian(rAU, p) == fvc::div(phiHbyA)
                );

                pEqn.setReference(pRefCell, pRefValue);
                pEqn.solve();

                if (nonOrth == nNonOrthCorr)
                {
                    phi = phiHbyA - pEqn.flux();
                }
            }

            #include "continuityErrs.H"

            U = HbyA - rAU*fvc::grad(p);
            U.correctBoundaryConditions();
        }

        runTime.write();

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;


    // Get index of patch
	const word w0("fixedWalls");
	const word w1("movingWall");
	const word w2("frontAndBack");
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

    // Get reference to boundary value
	const fvsPatchVectorField& faceCentreshub = mesh.Cf().boundaryField()[w0PatchID];  // const fvsPatchVectorField
    fvPatchVectorField& U_b = U.boundaryField()[w1PatchID]; // fvPatchVectorField
    
    // get coordinate for cell centre
    const fvPatchVectorField& centre = mesh.C().boundaryField()[w0PatchID];
    scalarField y = centre.component(vector::Y);
    scalarField x = centre.component(vector::X);
    
    // calculate inlet velocity
    //U_b = y*0.75/0.0051*vector (1,0,0)+x*0.75/0.0051*vector(0,1,0)+7.5*vector(0,0,1);
    
    //inletU.write();
	forAll(U_b, faceI)
	{
		const double PI = 3.14;
		//get coordinate for face centre
		const vector& c = faceCentreshub[faceI];
		//vector p(0.5*(1+Foam::sin(40*PI*c[0]-PI/2)), 0, 0);
		//if (c[0]>0.025 & c[0]<0.075)
	    //vector p1 = vector(1, 0, 0); 
		//vector p1(1, 0, 0);
		
		//U_b[faceI] = p1;
		Info<< "faceI = " << faceI 
			<< "c = "<< c 
			<< "U = "<< U_b[faceI] 
			<< endl;
	}
    
    Info<< "ExecutionTime = "
    << runTime.elapsedCpuTime()
    << " s\n\n" << endl;

    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
