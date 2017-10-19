#include "Point.H"

class Vector
{
public:
	Point start, end;

	Vector(Point, Point);
	Vector(double, double, double, double);
	void print();
};
