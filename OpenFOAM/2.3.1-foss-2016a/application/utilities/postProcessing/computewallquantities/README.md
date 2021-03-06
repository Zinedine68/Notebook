# computeWallQuantities
Utility for computing several quantities at wall-patches.
Inteded use is post-processing of LES data.

## source
This is the original version from
https://bitbucket.org/lesituu/computewallquantities

## Computed quantities
The utility will compute the following quantities:

1. yPlus

2. pMean -- intended for computing Cp.

3. uTau

4. Distance to nearest wall.

## Accepted command-line arguments
1. Common time-related arguments such as -latestTime

2. -wallModel, which will force including nuSgsMean when computing the wall-shear stress.

3. -noMeanFields, which will force the utility to used instanteneous fields: U, p and nuSgs, istead of the averaged.

## Requirements
The pMean and UMean fields should be present (or p and U in case of -noMeanFields).

If -wallModel is used, nuSgsMean should be present (or nuSgs in case of -noMeanFields).

## Output format
A separate file for each quantity is produced in ./postProcessing/computeWallQuantities/*time*/.

The format is dsv, where each line contains the x, y and z coordinate of the face center followed the the value of the quantity.
