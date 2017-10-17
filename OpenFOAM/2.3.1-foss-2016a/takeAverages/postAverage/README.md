# postAverage

## source
https://www.cfd-online.com/Forums/openfoam-programming-development/70396-using-fieldaverage-library-average-postprocessing.html

## Functionality
Time-average of the field of the output time dirs.
An app version of fieldAverage.

## Input
A dictionary in system/controDict 
Object to be averaged can be scalar, vector or tensor.

## Output
Mean Prime2Mean 

## How
post        : postAverage

## Limit
1. Same as fieldAverage
2. The field to be averaged needs to be added to createFields.H and thus recompile the app
3. in the dictionary : `ouputControl timeStep;` is needed.

# Cope with limit
Same as fieldAverage
