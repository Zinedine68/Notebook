# wallShearStress

## source
OF-2.3 official version

## Functionality
Calculate the stress/force on the wall, which contains not only a shear component but also a normal component.
```latex
T = \tau \cdot n
```

## Input
U

## Output
vector wallShearStress on wall

## How
wallShearStress (by defaut incompressible so everything is divided by rho already meaning uTau=sqrt(wallShearComponent)). However running in OF-2.3 needs a RASProperties where in a laminar case specifying `RASModel	laminar`

## Limit

# Cope with limit

# Dig the mine of OpenFOAM
