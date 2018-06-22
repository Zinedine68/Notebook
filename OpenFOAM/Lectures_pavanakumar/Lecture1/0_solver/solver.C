#include "fvCFD.H"

int main(int argc, char *argv[])
{
	#include "setRootCase.H"
	/*
    	Foam::argList args(argc, argv);
    	if (!args.checkRootCase())
    	{
        	Foam::FatalError.exit();
    	}
	*/
	#include "createTime.H"

	// create mesh and fields
	//

	while( runTime.loop() ) {
		Info << "Time : " << runTime.timeName() << "\n";	
		//
		runTime.write(); // write all IOobject related to runTime
	}
}
