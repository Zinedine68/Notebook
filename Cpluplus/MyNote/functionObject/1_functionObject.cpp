#include <iostream>

// source : https://www.quantstart.com/articles/Function-Objects-Functors-in-C-Part-1

// Abstract base class                                                                                                                                                                                                  
class BinaryFunction {
public:
  BinaryFunction() {};
  virtual double operator() (double left, double right) = 0;
};

// Add two doubles                                                                                                                                                                                                      
class Add : public BinaryFunction {
public:
  Add() {}; // constructor
  virtual double operator() (double left, double right) { return left+right; } // operator () of class Add
};

// Multiply two doubles                                                                                                                                                                                                 
class Multiply : public BinaryFunction {
public:
  Multiply() {};
  virtual double operator() (double left, double right) { return left*right; }
};

double binary_op(double left, double right, BinaryFunction* bin_func) {
  return (*bin_func)(left, right);
}

int main( ) {
  double a = 5.0;
  double b = 10.0;

  // BinaryFunction is an abstract base class thus cannot be instantiated
  // therefore use in binary_op passing by pointer
  BinaryFunction* pAdd = new Add(); // new Add[class][operator]();
  BinaryFunction* pMultiply = new Multiply();

  std::cout << "Add: " << binary_op(a, b, pAdd) << std::endl;
  std::cout << "Multiply: " << binary_op(a, b, pMultiply) << std::endl;

  delete pAdd;
  delete pMultiply;

  return 0;
}
