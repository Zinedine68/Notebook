# postAverage

## source
https://www.cfd-online.com/Forums/openfoam-programming-development/70396-using-fieldaverage-library-average-postprocessing.html

## Functionality
Time-average of the field of the output time dirs.
An app version of fieldAverage.

## Input
A dictionary in system/controDict 
Object to be averaged can be scalar, vector or tensor.

## Input
Mean Prime2Mean 

## How
post        : postAverage

## Limit
Same as fieldAverage
The field to be averaged needs to be added to createFields.H and thus recompile the app

# Cope with limit
Same as fieldAverage
