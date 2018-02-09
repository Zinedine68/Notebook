# computewallquantitiesV2

## source
https://bitbucket.org/lesituu/computewallquantities

## Functionality
In contrast to the version V1, this one calculate the coordinates and put it in a 
VolVectorField called "coor" but the real values are stored in `boundaryField()`
like yPlus. But this time in a general patch not the "wall patch". To simplify: only
the first time step is considered.

## Input

## Output
0/coor   
Value of the coordinates will be written into `0/coor`'s subDictionary 'Port1' typed as
`calculated`. So the data is then readable and manipulatable by paraview.   
./postProcessing/computeWallQuantities"/runTime.timeName()/currPatch.name()/yCoor   
Plain text file for the same data

## How
computeWallQuantitiesV2 -noMeanFields -time '0' 

## Limit
variables calculated are all wall-related thus only visible at wall. When visualizing by
paraview, need to choose only "wall" to get to display these quantities in the right way. 

# Cope with limit
cannot write a boundaryField (in code d.write() does not work as expected). Don't know how
to cope with the limit.
