//#include "fvCFD.H"

#include "argList.H"
#include "dimensionedType.H"
//using namespace Foam;

int main( int argc, char *argv[] ) {

	Foam::argList::validArgs.append("someFloatToConvert");
	Foam::argList args(argc, argv);
	// Foam : output with " "
	Foam::Info << "args[1] : " << args[1] << Foam::endl;
	// std  : output without " "
	std::cout << "args[1] : " << args[1] << std::endl;
	Foam::scalar d = atof(args[1].c_str());
	Foam::Info << "d : " << d << Foam::endl;

	return 0;
}
