# cellSetReader

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

# Dig the mine of OpenFOAM
