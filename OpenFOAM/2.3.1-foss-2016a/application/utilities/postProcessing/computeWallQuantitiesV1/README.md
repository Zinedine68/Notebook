# computewallquantitiesV1

## source
https://bitbucket.org/lesituu/computewallquantities

## Functionality
In contrast to the original one, this version compute yPlus, uTau, dist (distance to wall)
and write them in openfoam format so that it is readable by paraview and works for more
complex goemetry while the original writes a plain text file which is not easily visualizable.

## Line
### viscosity
readTransportProperties.H for variable nu (dimensionedScalar)   
initialize nuLam (volScalarField) by nu   
initialize nuEff (volScalarField) by nuLam   
if `wallModel` modify nuEff, if not nuEff has the same value as nu    
### uTau
```cpp
uTau.boundaryField()[patchI]=
     sqrt(                                             // sqrt (
          nuEff.boundaryField()[patchI]                // 	nu
         *mag(UMean.boundaryField()[patchI].snGrad())  // 	* mag(surface normal gradient of UMean)
     );                                                // )
```

## Input
UMean if not U

## Output
yPlus, uTau, dist

## How


## Limit
### visualization
variables calculated are all wall-related thus only visible at wall. When visualizing by
paraview, need to choose only "wall" to get to display these quantities in the right way.

# Cope with limit
cannot write a boundaryField (in code d.write() does not work as expected). Don't know how
to cope with the limit.

# Dig the mine of OpenFOAM
function `abs` doesn't work with a field. But `mag` does as well as `cmptMag`   

What is then `snGrad()`?   
if input is vectorField result is a vectorField, if input is scalarField result will be also a scalarField.
It is actually a gradient more precisely a `surface normal gradient`.
