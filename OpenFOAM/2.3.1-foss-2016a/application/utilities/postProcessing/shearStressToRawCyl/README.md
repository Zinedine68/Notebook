# shearStressToRawCyl

## Prototype
from wallShearStressToRaw

## Functionality
output cylindrical coordinate of the patch `wall`

## How To Use
need `convertToCylindrical` before this to get file `cCyl`

## Limit
parallel run gives a wrong result.   

## Cope with limit

## Note
`cCyl` has both `internalField()` (accessed by `faceCells`) and `boundaryField()`. Two solutions are both implemented. One commented.
