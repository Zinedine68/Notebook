# computewallquantitiesV3

## source
https://bitbucket.org/lesituu/computewallquantities

## Functionality
In contrast to the version V2, this one read a dictionary or more specifically a "labelList"
from file which can be a list a cell labels extracted from paraview.

## Input

## Output

## How
Use Paraview to choose the interested cells and use the spreadSheetView to get the selected
cell info in an excel file then export with defaut options. How to choose cells conveniently?
Try Edit->Find and choose a range of y-coordinates (bigger than, smaller than, between). But
only one variable can be conditioned. How do you get the y-coord into the scope? Calculator
using defaut point data to get the vector "Coord" and then apply filter "point data to cell 
data" then you hit the Edit->Find.     

In current test case, I want to get the cellID say along the y-axis sorting by yCoord from 
small to big value. Just sort the excel file and get the cellID which is local to patch "inlet".
Then you can actually get the coordinates in the utility by refering "Cf()" or you already 
have them in the excel.   

computeWallQuantitiesV2 -noMeanFields -time '0' 

## Limit
Only one variable is conditioned using paraview.

# Cope with limit
