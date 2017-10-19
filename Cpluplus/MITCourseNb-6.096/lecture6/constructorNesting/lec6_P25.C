#include "Vector.H"

int main() {

	//Vector v;
	//v.print();

	Point P1(3.0, 4.0);
	Point P2(5.0, 6.0);

	P1.print();
	P2.print();

	Vector v(3, 4, 5, 6);
	v.print();

	Vector v1(P1, P2);
	v1.print();

	Vector v2(Point(1,2), Point(3,4));
	v2.print();

	Point(99,99).print();
}
