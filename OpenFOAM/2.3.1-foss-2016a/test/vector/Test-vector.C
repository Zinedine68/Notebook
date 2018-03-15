#include "vector.H"
#include "IOstreams.H"

using namespace Foam;

int main()
{
    Info<< vector::zero << endl
        << vector::one << endl
        << vector::dim << endl
        << vector::rank << endl;

    vector d(0.5, 0.5, 0.5);
	Info<< "d = " << d << endl;
	//Info<< "d^2 = " << sqr(d) << endl;
	d.replace(vector::X, pow(d.component(vector::X), 2));
	d.replace(vector::Y, pow(d.component(vector::Y), 2));
    d.replace(vector::Z, pow(d.component(vector::Z), 2));
	Info<< "d^2 = " << d << endl;
    d /= mag(d);

    vector dSmall = (1e-100)*d;
    dSmall /= mag(dSmall);

    Info<< (dSmall - d) << endl;

    d *= 4.0;

    Info<< d << endl;

    Info<< d + d << endl;

    Info<< magSqr(d) << endl;

    vector d2(0.5, 0.51, -0.5);
    Info<< cmptMax(d2) << " "
        << cmptSum(d2) << " "
        << cmptProduct(d2) << " "
        << cmptMag(d2)
        << endl;
    Info<< min(d, d2) << endl;
    return 0;
}
