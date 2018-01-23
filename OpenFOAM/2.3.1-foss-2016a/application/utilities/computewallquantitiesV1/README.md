# computewallquantitiesV1

## source
https://bitbucket.org/lesituu/computewallquantities

## Functionality
In contrast to the original one, this version compute yPlus, uTau, dist (distance to wall)
and write them in openfoam format so that it is readable by paraview and works for more
complex goemetry while the original writes a plain text file which is not easily visualizable.

## Input
UMean if not U

## Output
yPlus, uTau, dist

## How


## Limit
variables calculated are all wall-related thus only visible at wall. When visualizing by
paraview, need to choose only "wall" to get to display these quantities in the right way. 

# Cope with limit
cannot write a boundaryField (in code d.write() does not work as expected). Don't know how
to cope with the limit.
