#include "Vector.H"
#include <iostream>

void Vector::print(){
	std::cout<< "start Point: "
			<< "(" << start.getX() << "," << start.getY() << ")"
			<< std::endl;
	std::cout<< "end   Point: "
			<< "(" << start.getX() << "," << start.getY() << ")"
			<< std::endl;
}

Vector::Vector(Point p1, Point p2):start(p1),end(p2)
{
}

Vector::Vector(double x1, double y1, double x2, double y2)
: start(x1, y1), end(x2, y2)
{
}

/*
Vector::Vector(double x1, double y1, double x2, double y2)
{
	this-> start = Point(x1, y1);
	this-> end   = Point(x2, y2);
}
*/
