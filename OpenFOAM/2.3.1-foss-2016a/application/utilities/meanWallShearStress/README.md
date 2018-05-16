# meanWallShearStress

## Prototype
wallShearStress from standard OpenFOAM library.

## Functionality
Calculate wallShearStress using UMean

## How To Use
meanWallStress -time 'timeStepWhereStoresUMean'

## Limit


## Cope with limit

## Note
0. meanWallShearStress may be negative (in a component's sense)
1. Calculate the "mean" stress/force on the wall, which contains not only a shear component but also a normal component.
T = tau . n   
2. By defaut incompressible so everything is divided by rho already meaning uTau=sqrt(wallShearComponent)). However running in OF-2.3 needs a RASProperties where in a laminar case specifying `RASModel laminar`
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
