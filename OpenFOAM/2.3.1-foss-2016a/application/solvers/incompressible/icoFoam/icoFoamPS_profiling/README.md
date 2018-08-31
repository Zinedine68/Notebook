# icoFoamPS_profiling

## Prototype
icoFoam added with passiveScalar T

## Functionality
with `<ctime>` we write to file `userDefinedLog/dataWritingHistory` the actual output time names

## How To Use
icoFoamPS_profiling > log
mpirun -n 4 icoFoamPS_profiling -parallel > log (only the master process will write)

## Limit

## Cope with limit

## Note
Even if you changed the output interval at **run time** the output time names will adapt to be the `changed` ones. (Why? The call runTime.outputTime is calculated at run time) In a word, what is inside the file is the real output time names of your simulation even if you changed deltaT or output interval at run time.
