#include "fvCFD.H"
#include "complexFields.H"

int main(int argc, char *argv[])
{

	complex a(scalar(3), scalar(4));

	complex a1(scalar(1), scalar(4));
	complex a2(scalar(2), scalar(5));
	complex a3(scalar(3), scalar(6));
	
	//complexField cfa{a1, a2, a3};  //wrong
	//complexField cfa(a1, a2, a3);  //wrong
	//List<complex> l = (a1, a2, a3);//wrong
	List<complex> l = {a1, a2, a3};
	Info << "List<complex> l = " << l << endl;
	complexField cfa(l);
	Info << "complexField cfa = " << cfa << endl;
	Info << "complexField Re(cfa) = " << Re(cfa) << endl;
	Info << "complexField ImComplexField(Re(cfa)) = " << ImComplexField(Re(cfa)) << endl;
	Info << "complexField mag(cfa) = " << mag(cfa) << endl;  //I believe this is because in "Field" this is implemented. But how does a mag(vectorField) and mag(complexField) call mag(vector) and mag(complex). How does the program do this?
	scalarField magcfa(cfa.size());
	forAll(cfa, i)
	{
		magcfa[i] = mag(cfa[i]);
	}
	Info << "magcfa = " << magcfa << endl;
	//List<complex> l1 = {a1.Re(), a2.Re(), a3.Re()}; //wrong left : complex = right : scalar. Not the same type. Though mathematically a scalar is a complex
	//List<complex> l2 = {a1.Im(), a2.Im(), a3.Im()};
	List<scalar> l1 = {a1.Re(), a2.Re(), a3.Re()};
	List<scalar> l2 = {a1.Im(), a2.Im(), a3.Im()};
	//complexField cfa1(l1, l2);                      //wrong. Error message is all "Field with type = complex" not "complexField"  Don't know why. ./OpenFOAM/fields/Fields/complexFields/complexFields.C:42 I think this is a constructor

	complexVector v(a, a, a);	
	Info << "complexVector v = " << v << endl;
	List<complexVector> lcv{v, Foam::complexVector::one, Foam::complexVector::zero};
	Info << "List<complexVector> lcv = " << lcv << endl;
	complexVectorField cvf(lcv);
	Info << "complexVectorField cvf = " << cvf << endl;
	Info << "complexVectorField Re(cvf) = " << Re(cvf) << endl;
	//Info << "complexVectorField cfa^cvf = " << cfa^cvf << endl; //wrong. Because complex^complexVector is already wrong.

}
