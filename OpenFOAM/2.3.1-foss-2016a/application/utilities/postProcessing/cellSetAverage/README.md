# cellSetAverage

## source

## Functionality
read `constant/polyMesh/sets/someCellSet` = output of topoSet (cellSet)   
read `U` in time directories   
calculate volume average of `U` projected in direction `flowDir_` (hard coded) in cellSet

## Input
timeDir containing U   
constant/polyMesh/standardMeshFiles   
system/controlDict   

constant/polyMesh/sets/someCellSet from topoSet
hard coded `flowDir_`

## Output
standard output `magUbarAve`

## How
cellSetReader -time 'someTime'

## Limit
`flowDir_` hard coded

# Cope with limit
加上“输出到文件”

# Dig the mine of OpenFOAM
Dependancy on meshTools is due to `cellSet.H` is there.

the file constant/polyMesh/sets/someCellSet will be of class "cellSet". But... actually it's a labelList. So normaly instead of constructing a `cellSet`, a `labelList` may also do the trick. In the sense that you can modify the file to read as the original/general type so openfoam will treat it as a `labelList` instead of `cellSet`.
