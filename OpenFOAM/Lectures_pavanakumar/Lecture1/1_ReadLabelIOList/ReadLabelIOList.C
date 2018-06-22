#include "fvCFD.H"

int main(int argc, char *argv[])
{
	Info << "Hello world" << endl;

	#include "setRootCase.H"
	#include "createTime.H"

	//labelIOList some = labelIOList // this is assignement
	labelIOList some                 // this is from constructor
	(
	 	IOobject
		(
			"some",
	    	"",
			runTime,
			IOobject::MUST_READ,	
			IOobject::NO_WRITE,
			false /// Does not register with objectRegistry
		)
	);

	Info << "some : " << some << endl;
	Info << "begin write runTime : " << endl;
	runTime.write(); // normally "some" as IOobject will not be written. Since it's not registered in runTime or even if it's registered, NO_WRITE flag is on. Tried once to MUST_READ and AUTO_WRITE, the original file is overridden (but I'm not perfectly sure).
	Info << "end write runTime : " << endl;

	return 0;
}
