//#include <iostream>   // it seems std is included now through messageStream.H
                        // my guess is through forward declaration of class IOstream of OpenFOAM
#include "messageStream.H"

int main(int argc, char * argv[]){
    int i;
    for(i = 0; i < argc; i++){
        std::cout << "Argument "<< i << " = " << argv[i] << std::endl;
    }

    for(i = 0; i < argc; i++){
		Foam::Info << "Argument "<< i << " = " << argv[i] << Foam::endl;
    }
    return 0;
}
