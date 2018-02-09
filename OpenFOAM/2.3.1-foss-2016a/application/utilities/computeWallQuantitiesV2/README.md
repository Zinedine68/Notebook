# computewallquantitiesV2

## source
https://bitbucket.org/lesituu/computewallquantities

## Functionality
In contrast to the version V2, this one calculate the distance to wall of all cells on
a patch and put the data in a VolVectorField called "r" but the real values are stored
 in `boundaryField()` like yPlus. 

## Input

## Output
0/r  

## How
computeWallQuantitiesV2 -noMeanFields -time '0' 

## Limit
variables calculated are all patch-related thus only visible at wall. When visualizing by
paraview, need to choose only "patch" to get to display these quantities in the right way. 

# Cope with limit
