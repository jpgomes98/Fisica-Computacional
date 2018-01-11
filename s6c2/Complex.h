#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

class Complex{
  double Re;
  double Im;
  double norm;
public:
  Complex();
  Complex(double x, double y);
  Complex(const Complex& z);
    
  double getNorm() const;
  double printRe() const;
  double printIm() const;
  Complex conj();

  void operator()(double x, double y);
  Complex& operator=(const Complex& z);
  Complex operator+(const Complex& z);
  Complex operator-(const Complex& z);
  Complex operator*(const Complex& z);
  Complex operator/(const Complex& z);
  
  bool operator==(const Complex& z);
  bool operator!=(const Complex& z);

  /* Friends */
  friend ostream& operator<<(ostream& out, const Complex& z);
  
};


#endif
