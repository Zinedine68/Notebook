//#include "fvCFD.H"

#include "argList.H"
#include "dimensionedType.H"
using namespace Foam;

int main( int argc, char *argv[] ) {

	Info << "argv[1] : " << argv[1] << endl;;
	//double d = atof((argv[1]).c_str());
	double d = atof(string(argv[1]).c_str());
	Info << "d/2.0 : " << d/2.0 << endl;

	dimensionedScalar inputPressure =
	dimensionedScalar
	(
		"pressure", /// A name field
		dimensionSet( 1, -1, -2, 0, 0, 0, 0 ),
		2.0 /// Value to initialize
	);
	Info << inputPressure << "\n";

	dimensionedScalar Mach =
	dimensionedScalar
	(
		"Ma", /// A name field
		dimless,
		1.0 /// Value to initialize
	);
	Info << Mach << "\n";

	//scalar M;
	//args.optionRead("mach", M);
	//args.optionRead("mach");

	//inputPressure = Mach;
	inputPressure.value() = Mach.value();
	Info << "after value() assignement " << endl;
	Info << inputPressure << "\n";
	Info << Mach << "\n";

	//Info << "args[1] : " << atof(args[1].c_str())/2.0 << endl;
	//Mach.value()=atof(args[1].c_str())/2.0;
	Info << Mach << "\n";

	return 0;
}
