
# output locations of utilities

## postChannel 
folder "graphs"   
coordinates in the output : y_ = mesh.cellCentres()

## postChannelFlow 
folder "postProcessing/collapsedFields"   
coordinates in the output : y_ = mesh.cellCentres()

## computeWallQuantities 
folder "postProcessing/computeWallQuantities"   
coordinates in the output : face centres : Cf() : currPatch.Cf()[faceI].component(vector::X)

## KineticEnergy 
folder "fieldStatistics"
