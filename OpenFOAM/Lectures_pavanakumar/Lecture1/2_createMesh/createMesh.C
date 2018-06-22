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
	#include "createTime.H"            // system/controlDict
	/*
    	Foam::Info<< "Create time\n" << Foam::endl;

    	Foam::Time runTime(Foam::Time::controlDictName, args);
	*/

	// create mesh and fields
	//
	#include "createMesh.H"           // polyMesh/* ; system/fvSchemes ; system/fvSolution
/*
    Foam::Info
        << "Create mesh for time = "
        << runTime.timeName() << Foam::nl << Foam::endl;

    Foam::fvMesh mesh
    (
        Foam::IOobject
        (
            Foam::fvMesh::defaultRegion,
            runTime.timeName(),
            runTime,
            Foam::IOobject::MUST_READ
        )
    );
*/
	/*
	while( runTime.loop() ) {
		Info << "Time : " << runTime.timeName() << "\n";	
		//
		runTime.write(); // write all IOobject related to runTime
	}
	*/

	return 0;
}
