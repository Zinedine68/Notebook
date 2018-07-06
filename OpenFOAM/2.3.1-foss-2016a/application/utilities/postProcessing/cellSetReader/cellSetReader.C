#include "fvCFD.H"
#include "cellSet.H"

int main( int argc, char *argv[] ) {

    Info << "Hello FOAM!" << endl; 

	//argList::validArgs.append("flowDir");
	#include "setRootCase.H"
	//vector flowDir_ = vector(args[1]); // this is not working
    #include "createTime.H"
    #include "createMesh.H"

	cellSet cells_
	(
    	IOobject
    	(
        	"cylTurbGenerator",
			"constant/polyMesh/sets",
        	mesh,// I have to stay with you, right ?! For now.
        	IOobject::MUST_READ,
        	IOobject::NO_WRITE
    	)
	);

	//volField<vector> U  // this is not working
	volVectorField U
	(
		IOobject
	    (
			"U",
		    runTime.timeName(),	
			mesh,
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE		
		),	
	mesh
	);

	Info << "cells_ size : " << cells_.size() << endl;
	Info << "U size : " << U.size() << endl;

	vector flowDir_ = vector(0, 0, 1);
	scalar magUbarAve = 0.0;
	scalar V_ = 0.0;
	const scalarField& cv = mesh.V();
	forAll(cells_, i)
	{
		label cellI = cells_[i];
		scalar volCell = cv[cellI];
		magUbarAve += (flowDir_ & U[cellI])*volCell;
		V_ += volCell;
	}

	magUbarAve /= V_;

	Info << "magUbarAve in direction "
		<< flowDir_
		<< " : " << magUbarAve << endl;

    return 0;
}
