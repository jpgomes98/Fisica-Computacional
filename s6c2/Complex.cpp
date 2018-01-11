#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "Complex.h"

using namespace std;


/* Construtores */

Complex::Complex()
{
  Re = 0;
  Im = 0;
  norm = 0;
}

Complex::Complex(double x, double y)
{
  Re = x;
  Im = y;
  norm = sqrt(x * x + y * y);
}

Complex::Complex(const Complex& z)
{
  Re = z.Re;
  Im = z.Im;
  norm = z.norm;
}

double Complex::getNorm() const
{
  return sqrt(Re*Re + Im*Im);
}

double Complex::printRe() const
{
  return Re;
}

double Complex::printIm() const
{
  return Im;
}

Complex Complex::conj()
{
  Complex res(*this);
  res.Im = -Im;
  return res;
}

void Complex::operator()(double x, double y)
{
  Re = x;
  Im = y;
  norm = sqrt(x * x + y * y);
}

Complex& Complex::operator=(const Complex& z)
{
  Re = z.Re;
  Im = z.Im;

  return (*this);
}

Complex Complex::operator+(const Complex& z)
{
  Complex res;

  res.Re = Re + z.Re;
  res.Im = Im + z.Im;

  return res;
}

Complex Complex::operator-(const Complex& z)
{
  Complex res;
  res.Re = Re - z.Re;
  res.Im = Im - z.Im;
  return res;
}


Complex Complex::operator*(const Complex& z)
{
  Complex res;
  res.Re = (Re * z.Re - Im * z.Im);
  res.Im = (z.Re * Im + Re * z.Im);

  return res;
}

Complex Complex::operator/(const Complex& z)
{
  Complex res;
  res.Re = (Re * z.Re + Im * z.Im) / (z.getNorm() * z.getNorm());
  res.Im = (z.Re * Im - Re * z.Im) / (z.getNorm() * z.getNorm());

  return res;
}

bool Complex::operator==(const Complex& z)
{
  if((Re == z.Re) && (Im == z.Im)){
    return true;
  }

  else{
    return false;
  }
}

bool Complex::operator!=(const Complex& z)
{
  if((Re == z.Re) && (Im == z.Im)){
    return false;
  }

  else{
    return true;
  }
}


ostream& operator<<(ostream& out, const Complex& z)
{
  if (z.printIm() >= 0){
    out << z.printRe() << " + " << z.printIm() << "i";
  }
  else{
    out << z.printRe() << " - " << (-1) * z.printIm() << "i";
  }

  return out;
}
