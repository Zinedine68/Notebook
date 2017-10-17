# fieldAverage

## Functionality
Time-average of the field (registered in ObjectRegistry I guess).

## Input
A dictionary in system/controDict 
Object to be averaged can be scalar, vector or tensor.

## Input
Mean Prime2Mean 

## How
At run time : functionObject
post        : execFlowFunction

## Limit
Add field like U2 (U square by elements) in the dictionary, it won't calculate its mean
```cpp
--> FOAM Warning :
    From function void Foam::fieldAverage::initialize()
    in file fieldAverage/fieldAverage/fieldAverage.C at line 92
    Field U2 not found in database for averaging
```

# Cope with limit
But add U2 as a volVectorField into the createFields.H. That will do.
