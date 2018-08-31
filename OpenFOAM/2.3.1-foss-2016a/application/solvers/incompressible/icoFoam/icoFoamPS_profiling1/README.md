# icoFoamPS_profiling1
and its python and bash tools

## Prototype
icoFoam added with passiveScalar T

demo0 and reconstruct0.sh are prototype

## Functionality
with `<time.h>` we write to file `userDefinedLog/dataWritingHistory` the actual output time names with (local time is commented for now)

demo2.py and reconstruct2.sh are meant to get from `userDefinedLog/dataWritingHistory` the list of time names which are already written and avoid the last time written (because I'm not sure if the writting is finished or not). Then remove them in its **decomposed** form thus dimunish largely the number of files.

## How To Use
icoFoamPS_profiling1 > log
mpirun -n 4 icoFoamPS_profiling1 -parallel > log (only the master process will write)

## Limit
demo2 and reconstruct2 has only the main function. Still need to pay some attention to details.

## Cope with limit

## Note
