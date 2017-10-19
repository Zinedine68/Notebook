#include "Point.H"
#include <iostream>

void Point::print()
{
	std::cout<<"(x, y): "	
			<<"("
			<< this->getX()
			<<", "
			<< this->getY()
			<<")"
			<< std::endl;
}

Point::Point(double xcoord, double ycoord)
{
	x = xcoord;
	y = ycoord;
}

double Point::getX()
{
	return x;	
}

double Point::getY()
{
	return y;	
}
