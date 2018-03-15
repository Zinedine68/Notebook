# postAverage1

## source
cfd-forum : https://www.cfd-online.com/Forums/openfoam-programming-development/70396-using-fieldaverage-library-average-postprocessing.html

## Functionality

## Input 
volScalarField

## Output
volScalarField_mean

## How
postAverage1 p -time '20:40'   
this will do the average of p between time '20:40'

## Limit
only works for volScalarField

# Cope with limit

# Dig the mine of OpenFOAM

# bug
dimension error:
```cpp
--> FOAM FATAL ERROR: 
Different dimensions for +=
     dimensions : [0 2 -2 0 0 0 0] = [0 4 -4 0 0 0 0]


    From function dimensionSet::operator+=(const dimensionSet&) const
    in file dimensionSet/dimensionSet.C at line 185.

FOAM aborting

#0  Foam::error::printStack(Foam::Ostream&) at ??:?
#1  Foam::error::abort() at ??:?
#2  Foam::dimensionSet::operator+=(Foam::dimensionSet const&) const at ??:?
```
