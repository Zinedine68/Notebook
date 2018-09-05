# nonNewtonianIcoFoamPS_profiling1

## Prototype
nonNewtonianIcoFoam added with passiveScalar T and profiling

## Functionality

## How To Use

## Limit
output `nu`? Or leave it to post-processing

## Cope with limit
修正 Note 中 2. nonNewtonianIcoFoam 是自动输出 nu 的，输出boundaryField type是`calculated`, 而我自己的这版nonNewtonianIcoFoamPS_profiling1仅仅加入`DT`，而没有修改其他的输出，因此也是runTime.write()将`nu, p, phi, T, U`一齐输出

## Note
1. At the beginning of simu : "Create mesh, no clear-out for time = 0" is perfectly normal. Because in this solver we have #include `"createMeshNoClear.H"` instead of `#include "createMesh.H"` though I don't know why.
2. no `nu` is output though... it is created as IOobject at some place `Foam::viscosityModels::BirdCarreau::BirdCarreau` and it is `IOobject::AUTO_WRITE`. Anyhow there's no `nu` output in my test of **standard** nonNewtonianIcoFoam.
