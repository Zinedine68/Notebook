
## Test-sortList

## Requirement
File : No mesh class is involved however the "runTime" is which inquires system/controDict   
File : myList   
File : myDictFile   

## modification
Read a labelList from file "myList"   
Read a labelList from file "myDictFile" using IOdictionary, myList1 is read as a dictionary   
Read a dimensionedScalar using IOdictionary   
Read a scalar ==> failed

## Dig the mine of OpenFOAM
function sort() <== UList::sort() <== std::sort()
In class `List<T>` there's no decleration of `function sort()`
