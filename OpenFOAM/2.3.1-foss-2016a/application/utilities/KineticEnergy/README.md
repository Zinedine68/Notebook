# KineticEnergy

## source
last version's bug : have a 'l' at every timeStep Name.   
fix it by putting the std:: before almost everything used in stdc++ except the 'c_str()'

## Functionality
Read U and calculate the sqr(U) volScalarField then a volume average (scalar).

## Input
U

## Output
TKE (athmetic sum of kinetic energy)
KE.weightedAverage(mesh.V()) (volume weighted average = volume integration / total volume)

## How
    KineticEnergy -time '99950'
    mpirun -n 4 KineticEnergy -time '99950' -parallel

## Limit
Never manage to use "sum" or "gsum" and "mesh.V()" to calculate the KE.weightedAverage(mesh.V()). 

# Cope with limit
Unary operator like "sum" and "gsum" seems to only accept a variable not two variable with a operation
from which the result is only one variable. Ex : sum(1.0 * KE) will not work. No deduction in this
macro-like functions ?

# Dig the mine of OpenFOAM
Another solution is to add "append" option to the OpenFOAM encapsulation of class OFstream by hjasak. Link here : [solution hjasak](https://www.cfd-online.com/Forums/openfoam-solving/58347-how-open-old-file-append.html)
