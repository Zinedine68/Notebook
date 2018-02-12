# computewallquantitiesV4

## source
https://bitbucket.org/lesituu/computewallquantities

## Functionality
Comparing to V3, clean out the wall part. Towards a clean utility only for meshes.
Using paraview to get a local labelList of cells on a patch and copy the list into a dictionary (file in constant dir) then read by utility and proceed.

## Developpment Approacheseses
1. "findCell" works with variable "mesh" not a patch, meaning it returns a global label for
an interior mesh. findCell by coordinates -> fail    
2. Use coordinates of face centers "Cf()" on a patch to filter down the cells I'm interested. -> V2   
3. Calculate "r" using coordinate of the patch center "ctr", thinking that sampling afterwards the patch data
will then give me a decent distribution of mesh location at the wall normal direction. No! Not that simple !
Because the sampling is always been done by a Number of sampling points (either for type "cellPoint" or "cell").
Yes, we can samping using a lot of sampling points while having "steps" using only "cell values". -> require python postTreatment which is not that self-evident. Picking out every mid-point of every step while recognizing steps.   
4. Read a local labelList of current patch from a third part (export from paraview) and acess
their info (like coordinates). And find out that they are actually slightly different (relative error: 10^-4). -> as long as picking the points from paraview is doable. This is the most convenient way for now.   

If we can improve approach 2 and find neighbor cellID using a direction vector (find cell along a direction) then cellIDs are sorted in a natural way. It will not be dependant on third party softs.
## Input

## Output
0/r  

## How
paraview export a labelList
copy the labelList to the specific file
computeWallQuantitiesV3 -noMeanFields -time '0' 

## Limit

# Cope with limit

## Dig the mine of OpenFOAM
```cpp
//Initialization of a volVectorField

        volVectorField coor
        (
           IOobject
           (
               "coor",
               runTime.timeName(),
               mesh,
               IOobject::NO_READ,
               IOobject::AUTO_WRITE
               ),
               mesh,
			   dimensionedVector("coor", dimLength, vector(0.0 , 0.0 , 0.0))
			   //dimensionedVector("coor", dimLength, (0.0 , 0.0 , 0.0)) // this doesn't work
         );


// Initialization of a labelListIOList (or read a labelListList from dictionary)

    //labelListIOList proximityCells  // this gives error labelListIOList is not in this scope
    IOList<labelList> proximityCells  // while this class is well recognized
    (
        IOobject
        (
            "proximityCells",
            runTime.time().constant(),
            mesh,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        )
    );

```
