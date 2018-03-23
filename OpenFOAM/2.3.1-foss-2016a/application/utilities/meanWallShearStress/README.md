# meanWallShearStress

## source
modified from OF-2.3 official version

## Functionality
Calculate the "mean" stress/force on the wall, which contains not only a shear component but also a normal component.
T = tau . n

## Line
### UMean
read UMean as entry stored in variable U   
calculate meanWallShearStress by `calcIncompressible(mesh, runTime, U, meanWallShearStress);` results are put in varirable meanWallShearStress
### meanShearStress
```cpp
    wallShearStress.boundaryField()[patchI] =
    (											// (
       -mesh.Sf().boundaryField()[patchI]       //   unit normal vector
       /mesh.magSf().boundaryField()[patchI]
    ) & Reff.boundaryField()[patchI];           // ) innerProduct with the stressTensor

//  for Reff
	const volSymmTensorField Reff(model->devRhoReff());	
//  if in RASProperties : laminar
//  should be in src/turbulenceModels/incompressible/RAS/laminar/laminar.C
	tmp<volSymmTensorField> laminar::devReff() const
	{
	    return tmp<volSymmTensorField>
	    (
	        new volSymmTensorField
	        (
	            IOobject
	            (
	                "devRhoReff",
	                runTime_.timeName(),
	                mesh_,
	                IOobject::NO_READ,
	                IOobject::NO_WRITE
	            ),
	           -nu()*dev(twoSymm(fvc::grad(U_)))
	        )
	    );
	}
```
## Input
UMean

## Output
vector meanWallShearStress on wall

## How
meanWallShearStress (by defaut incompressible so everything is divided by rho already meaning uTau=sqrt(wallShearComponent)). However running in OF-2.3 needs a RASProperties where in a laminar case specifying `RASModel	laminar`   
Maybe possible in parallel run also : to be tested

## Limit
meanWallShearStress may be negative

# Cope with limit

# Dig the mine of OpenFOAM
