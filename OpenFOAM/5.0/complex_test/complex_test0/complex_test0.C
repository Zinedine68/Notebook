#include "fvCFD.H"
//#include "complex.H"
#include "complexVector.H"

int main(int argc, char *argv[])
{

	complex a(scalar(3), scalar(4));
	Info << "complex Foam::complex::one = " << Foam::complex::one << endl;	
	Info << "complex a = " << a << endl;	
	Info << "complex 2*a = " << 2*a << endl;	
	Info << "complex a*a = " << a*a << endl;	
	Info << "complex mag(a) = " << mag(a) << endl;	

	Info << "complex Foam::complexVector::one = " << Foam::complexVector::one << endl;	
	Info << "complex Foam::complexVector::max = " << Foam::complexVector::max << endl;	
	complexVector v(a, a, a);	
	Info << "complexVector v = " << v << endl;
	Info << "complexVector complex::one * v = " << Foam::complex::one * v << endl;   // complexVectorI.H
	Info << "complexVector v / complex(1, -1) = " << v/complex(1, -1) << endl;   // complexVectorI.H
	//Info << "complexVector v&v = " << v & v << endl;   // complexVectorI.H     This doesn't work, why??

}
