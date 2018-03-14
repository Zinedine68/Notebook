# meanWallShearStress

## source
modified from OF-2.3 official version

## Functionality
Calculate the "mean" stress/force on the wall, which contains not only a shear component but also a normal component.
T = tau . n

## Input
UMean

## Output
vector meanWallShearStress on wall

## How
meanWallShearStress (by defaut incompressible so everything is divided by rho already meaning uTau=sqrt(wallShearComponent)). However running in OF-2.3 needs a RASProperties where in a laminar case specifying `RASModel	laminar`   
Maybe possible in parallel run also : to be tested

## Limit

# Cope with limit

# Dig the mine of OpenFOAM
