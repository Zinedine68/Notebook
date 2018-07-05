# TurbulentKineticEnergy_commandLineTime

## source
TurbulentKineticEnergy.C

## Functionality
linked to `UserPostCalc.o` which permits 1 command line argument

## Input
U_mean @ 'timeStepForMean'   
U @ other time steps

## Output
TTKE total turbulent kinetic energy   
turbulent intensity

## How
compile for `UserPostCalc.o`  
compile for TurbulentKineticEnergy_commandLineTime 
pre-calculate for U_mean @ time 'timeStepForMean'   
TurbulentKineticEnergy timeStepForMean -time 'startTime:timeStepForMean'

## Improvement
Add one command line argument to 'TurbulentKineticEnergy'   

## Limit
if time '0' is included and initial field is uniformly zero, initial turbulent intensity is then `-100%`.   
for every time step there is a output for KEMean which is extra.

# Cope with limit
The hard coded timeStepForMean is now a command-line argument.

# Dig the mine of OpenFOAM
