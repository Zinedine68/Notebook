#include "fvCFD.H"

int main( int argc, char *argv[] ) {

    // utility general info
    argList::addNote
    (
        "Calculates things.\n"
        "\n"
        "Input arguments:\n"
        "----------------\n"
        "  someWord - does stuff\n"
    );

    // prepare argument list
    argList::noParallel();
    argList::validArgs.append("someArgument");
    argList::validArgs.append("anotherArgument");
    
    // prepare options
    argList::addOption
    (
        "dict",
        "word",
        "Path to the dict file if different than './system/someDict'"
    );

    argList::addBoolOption
    (
        "pRelative",
        "Switches from A to B"
    );

    // create argument list
    Foam::argList args(argc, argv); // <- normally defined inside setRootCase.H
    if (!args.checkRootCase())
    {
        Foam::FatalError.exit();
    }

    Info << "args[0] = " << args[0] << endl;
	Info << "args[1]/3.0 = " << atof(args[1].c_str())/3.0 << endl;
	Info << "args[2]/4.0 = " << atof(args[1].c_str())/4.0 << endl;
	
	return 0;
}
