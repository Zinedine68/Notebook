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
上个版本不能够实现cellSetReader -time 'someTime'，仅仅是按照当前目录下所有的时间步来一步一步进行上诉计算，现在加入timeSelector可以实现仅仅对某个时间步算平均流场。要注意的是这里加上了一个forAll的时间循环，上一版没有加仍然可以循环（只是不受option -time 控制）。

# Dig the mine of OpenFOAM
Dependancy on meshTools is due to `cellSet.H` is there.

the file constant/polyMesh/sets/someCellSet will be of class "cellSet". But... actually it's a labelList. So normaly instead of constructing a `cellSet`, a `labelList` may also do the trick. In the sense that you can modify the file to read as the original/general type so openfoam will treat it as a `labelList` instead of `cellSet`.
