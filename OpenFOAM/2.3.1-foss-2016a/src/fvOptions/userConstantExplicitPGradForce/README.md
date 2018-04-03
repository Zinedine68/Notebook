# userConstantExplicitPGradForce 

## source
pressureGradientExplicitSource

## Functionality
For now just changed class name into userConstantExplicitPGradForce and make another Make/files Make/options for the new class. The interior is the same as pressureGradientExplicitSource

## Input
Ubar for flow_dir = Ubar / mag(Ubar)   
gradP0 is imposed as constant   
fieldNames : like (U)

## Output

## How
libs("libfvOptionUserConstantExplicitPGradForce.so"); in inside system/controDict

## Limit

# Cope with limit
