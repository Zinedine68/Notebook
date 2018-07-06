#include <iostream>

// source : https://www.quantstart.com/articles/Function-Objects-Functors-in-C-Part-1

/*
 * function pointer is not pointing a data value any more like other pointers.
 * It's a piece of code in memory to be executed. Dereferencing function 
 * pointer is to execute the function.
 *
 */

double add(double left, double right) {
    return left + right;
}

double multiply(double left, double right) {
    return left * right;
}

double binary_op(double left, double right, double (*f)(double, double)) {
    return (*f)(left, right);
}

int main( ) {
    double a = 5.0;
    double b = 10.0;

    std::cout << "Add: " << binary_op(a, b, add) << std::endl;
    std::cout << "Multiply: " << binary_op(a, b, multiply) << std::endl;

    return 0;
}
