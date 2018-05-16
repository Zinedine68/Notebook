# shearStressToRaw

## Prototype
wallShearStress from standard OpenFOAM library.

## Functionality
Read U field and calculate wallShearStress on patch "wall" then save the wallShearStress value at "wall" to a 6-colon data file for every time step.

## How To Use
shearStressToRaw -time '1:100'

## Limit
parallel run gives a wrong result.

## Cope with limit

## Note
