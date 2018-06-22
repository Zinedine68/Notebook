#include "fvCFD.H"
int main( int argc, char *argv[] ) {
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


	//inputPressure = Mach;
	inputPressure.value() = Mach.value();
	Info << "after value() assignement " << endl;
	Info << inputPressure << "\n";
	Info << Mach << "\n";

	return 0;
}
