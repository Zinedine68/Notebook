# TurbulentKineticEnergy

## source
TurbulentKineticEnergy

## Functionality
read U_mean @ '0.4' and calculate KEMean. Then (KE-KEMean) get the turbulent Kinetic Energy thus turbulent intensity.

## Input
U_mean @ '0.4'   
U

## Output
TTKE total turbulent kinetic energy   
turbulent intensity

## How
pre-calculate for U_mean @ time '0.4'
TurbulentKineticEnergy -time '0:0.4'

## Limit
time step '0.4' is hard coded   
if time '0' is included and initial field is uniformly zero, initial turbulent intensity is then `100%`.   
for every time step there is a output for KEMean which is extra.

# Cope with limit

# Dig the mine of OpenFOAM
