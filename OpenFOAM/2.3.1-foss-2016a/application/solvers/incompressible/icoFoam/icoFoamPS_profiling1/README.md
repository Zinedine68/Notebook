# icoFoamPS_profiling1

## Prototype
icoFoam added with passiveScalar T

## Functionality
with `<time.h>` we write to file `userDefinedLog/dataWritingHistory` the actual output time names with (local time is commented for now)

## How To Use
icoFoamPS_profiling1 > log
mpirun -n 4 icoFoamPS_profiling1 -parallel > log (only the master process will write)

## Limit

## Cope with limit

## Note
