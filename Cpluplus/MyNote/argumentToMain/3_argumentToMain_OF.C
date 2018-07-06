//#include <iostream>   // it seems std is included now through messageStream.H
                        // my guess is through forward declaration of class IOstream of OpenFOAM
#include "messageStream.H"
#include "argList.H"

int main(int argc, char * argv[]){
	//argList args(argc, argv);  // without Foam:: class argList is not recogized
	Foam::argList args(argc, argv);
	
    int i;
    for(i = 0; i < argc; i++){
        std::cout << "Argument "<< i << " = " << args[i] << std::endl;
    }

    for(i = 0; i < argc; i++){
		Foam::Info << "Argument "<< i << " = " << args[i] << Foam::endl;  // There is " " for a "Foam::string" object I imagine for "Foam::Info" ...
    }
    return 0;
}
