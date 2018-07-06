#include "fvCFD.H"

int main( int argc, char *argv[] ) {

	argList args(argc, argv);

	Foam::Time runTime
	(
		Foam::Time::controlDictName,
		args.rootPath(),
		args.caseName()
	);

	IOdictionary ioDictObj
	(
		IOobject
		(
			"myDictFile",
			"",
			runTime,
			IOobject::MUST_READ,
			IOobject::NO_WRITE
		)
	);

	vector vec_in = vector( ioDictObj.lookup("vec_in") ); // why need convert? What type to what type?
	vector vec_in1 ( ioDictObj.lookup("vec_in") );

	//Info << "lookup("vec_in") " << ioDictObj.lookup("vec_in") << endl;
	Info << "vec_in : " << vec_in << endl;
	Info << "vec_in1 : " << vec_in1 << endl;

	return 0;
}
