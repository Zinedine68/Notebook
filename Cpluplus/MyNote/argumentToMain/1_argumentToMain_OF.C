#include <iostream>

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
