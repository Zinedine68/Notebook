#include <iostream>

// source : http://www.bogotobogo.com/cplusplus/functors.php
//
// This example is more intuitive !
// Anything behaves like a function well... like absValue is a class/struct and "function" too.
// Because it can be used like below "aObj(-10.0)"

struct absValue   // struct ~ class
{
	float operator()(float f) {
		return f > 0 ? f : -f;
	}
};

int main( ) 
{ 
	using namespace std;

	float f = -123.45;
	absValue aObj;            // Here is an object, right?
	float abs_f = aObj(f);    // wait a minute! An object is used as if it's a function using "function(argument)" formalism
							  // From a more object point of view :
							  // aObj.operator()(f); is equivalent.
	cout << "f = " << f << " abs_f = " << abs_f << endl;
	return 0; 
}
