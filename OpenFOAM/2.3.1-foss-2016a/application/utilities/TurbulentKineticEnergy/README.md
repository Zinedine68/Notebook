# TurbulentKineticEnergy

## source
TurbulentKineticEnergy

## Functionality
read U_mean @ '150.4' and calculate KEMean. Then (KE-KEMean) get the turbulent Kinetic Energy thus turbulent intensity.   
read U_mean @ '150.4' and calculate tKE using `(U - UMean)(U - UMean)`. Then tKE/KEMean to get the TurbulentIntensity1

## Input
U_mean @ '150.4'   
U

## Output
file `fieldStatistics/KineticEnergy1`
turbulent intensity (Two definitions : indicated in Functionality)

## How
pre-calculate for U_mean @ time '150.4'
TurbulentKineticEnergy -time '150:0.4'

## Improvement

## Limit
time step '150.4' is hard coded    
if time '0' is included and initial field is uniformly zero, initial turbulent intensity is then `-100%` for one def but for the second def it is `100%`    
for every time step there is a output for KEMean which is extra.

# Cope with limit

# Dig the mine of OpenFOAM
