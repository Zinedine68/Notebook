#include "fvCFD.H"
#include "cellSet.H"

#include <fstream>
//using std::ofstream;

int main( int argc, char *argv[] ) {

    Info << "Hello FOAM!" << endl; 

	//argList::validArgs.append("flowDir");
	timeSelector::addOptions();
	#include "setRootCase.H"
	//vector flowDir_ = vector(args[1]); // this is not working
    #include "createTime.H"
	instantList timeDirs = timeSelector::select0(runTime, args);
    #include "createMesh.H"

	word dirName = word("postProcessing/fieldStatistics/sets");
	mkDir(dirName);
	word cellSetName = word("cylTurbGenerator");
	//Info << "dirName+cellSetName : " << dirName+cellSetName << endl;
	std::ofstream cellSetAveFile
	(
	    fileName(dirName+"/"+cellSetName).c_str(),
		std::ios_base::app
	);

	forAll(timeDirs, timeI)
	{
	    runTime.setTime(timeDirs[timeI], timeI);
        Foam::Info<< "Time = " << runTime.timeName() << Foam::endl;

	    cellSet cells_
	    (
    	    IOobject
    	    (
        	    cellSetName,
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

		cellSetAveFile << runTime.timeName().c_str()
			<< " " << magUbarAve << std::endl;

	}

    return 0;
}
