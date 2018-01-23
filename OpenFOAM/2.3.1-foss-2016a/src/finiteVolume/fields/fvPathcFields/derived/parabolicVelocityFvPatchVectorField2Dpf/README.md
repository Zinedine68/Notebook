# parabolicVelocityFvPatchVectorField2Dpf

## source
parabolicVelocityFvPatchVectorField

## Functionality
Bad naming but this class assign a 2D mean profile of Turbulent Boundary Layer and adding an envelopped fluctuation to a "circular patch".   
The non-dimensionized functions are implemented as non-member function

## Input
No input

## Output
Assign to fvPatchField

## How
Use it as every other boundary condition. Don't forget to compile/load the dynamic library which is named as "libparabolicVelocity2Dpf.so".

## Limit
1. Only the TBL is included, so no external flow. For my case now y+ equaling [1,80] and at 80 we arrive at the center of the tube.
2. Envelopes are extracted from "Reynolds number effects in a turbulent pipe flow for low to moderate Re, J. M. J. den Toonder, 1997". Approximated by polynomes. May have negative values at small value of yPlus.
3. When running in serial, output values of yPlus calculated at cells are correct. However when running in parallel, yPlus is always +-1e+300. But this output value does not influence the yPlus on the patch. MAYBE it is I initialized the variable as a field type. Not a boundaryField type !! So the initial values are random/GREAT.

# Cope with limit
