/*---------------------------------------------------------------------------*\
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

Global
    CourantNo

Description
    Calculates and outputs the maximum Courant Number.

\*---------------------------------------------------------------------------*/


scalar CoNum = 0.0;
scalar meanCoNum = 0.0;
//scalar waveCoNum = 0.0;

if (mesh.nInternalFaces())
{
    scalarField sumPhi
    (
        fvc::surfaceSum(mag(phi))().internalField()
    //  / h.internalField()
    );

    CoNum = 0.5*gMax(sumPhi/mesh.V().field())*runTime.deltaTValue();

	Info << "begin " << endl;
	//scalarField CFLField = 0.5*(sumPhi/mesh.V().field())*runTime.deltaTValue();  // this works for value conversion but CFLField is then permenantly downgraded to a scalar 
	//volScalarField CFLField(0.5*(sumPhi/mesh.V().field())*runTime.deltaTValue());
	CFLField.internalField() = 0.5*(sumPhi/mesh.V().field())*runTime.deltaTValue();
	/*
	Info << "here is the CFL"
			<< CFLField
			<< endl;
	*/
	Info << "end " << endl;
	Info << "size of CFLField" << CFLField.size() << endl;
	Info << "size of CFLField.internalField()" << CFLField.internalField().size() << endl;
	Info << "size of CFLField.boundaryField()" << CFLField.boundaryField().size() << endl;

    meanCoNum =
        0.5*(gSum(sumPhi)/gSum(mesh.V().field()))*runTime.deltaTValue();

	/*
    // Gravity wave Courant number
    waveCoNum = 0.25*gMax
    (
        fvc::surfaceSum
        (
            fvc::interpolate(sqrt(h))*mesh.magSf()
        )().internalField()/mesh.V().field()
    )*sqrt(magg).value()*runTime.deltaTValue();
	*/
}

	Info<< "Courant number mean: " << meanCoNum
	<< " max: " << CoNum << endl;

	// if commment the following 4 lines, CFLField will still be written by object runTime 
	// but every timeStep ignoring outputTime in controDict. Maybe because it's value is 
	// dependant on U and U is calculated and updated every time step.
	if(runTime.outputTime())
	{
		CFLField.write(); 
	}

//Info<< "Gravity wave Courant number max: " << waveCoNum
//    << endl;


// ************************************************************************* //

