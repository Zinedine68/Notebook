# icoFoamPS_profiling

## Prototype
icoFoam added with passiveScalar T

## Functionality
with `<ctime>` we write to file `userDefinedLog/dataWritingHistory` the actual output time names and the actual local time **after** finishing writing the last data.

## How To Use
icoFoamPS_profiling > log
mpirun -n 4 icoFoamPS_profiling -parallel > log (only the master process will write)

## Limit
format of the output time is like `18:8:19` which is ugly for minute.

## Cope with limit
Don't know the cure yet to replace `18:8:19` by `18:08:19`. Not that important for now though.

## Note
Even if you changed the output interval at **run time** the output time names will adapt to be the `changed` ones. (Why? The call runTime.outputTime is calculated at run time) In a word, what is inside the file is the real output time names of your simulation even if you changed deltaT or output interval at run time.
