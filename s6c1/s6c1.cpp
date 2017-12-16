#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

template <typename T>
class Complex{
  T Re;
  T Im;
  double norm;
public:
  explicit Complex();
  explicit Complex(T x, T y) {
    Re = x;
    Im = y;
    norm = sqrt(x * x + y * y);
  }

  double getNorm() const;
  T printRe() const;
  T printIm() const;

  Complex operator=(const Complex& z);
  Complex operator+(const Complex& z);

  /* Friends */
  template <class J>
  // é necessário especificar isto porque se trata de uma função da classe tratada à parte
  friend ostream& operator<<(ostream& out, const Complex<J>& z);
  
};

template <typename T> 
double Complex<T>::getNorm() const
{
  return norm;
}

template <typename T>
T Complex<T>::printRe() const
{
  return Re;
}

template <typename T>
T Complex<T>::printIm() const
{
  return Im;
}

template <typename T>
Complex<T> Complex<T>::operator=(const Complex<T>& z)
{
  Re = z.Re;
  Im = z.Im;

  return (*this);
}

template <typename T>
Complex<T> Complex<T>::operator+(const Complex<T>& z)
{
  Complex<T> res(0, 0);
  res.Re = Re + z.Re;
  res.Im = Im + z.Im;

  return res;
}

/* For friends only */

template <typename T>
ostream& operator<<(ostream& out, const Complex<T>& z)
{
  out << "\n";
  out << z.printRe() << " + " << z.printIm() << "i";
  out << "\n";

  return out;
}

int main()
{
  Complex<double> a(2, 3);
  Complex<double> b(1, 4);
  Complex<char> c('a', 't');

  cout << "Complexo a: ";
  cout << a;
  cout << "Complexo b: ";
  cout << b;
  cout << "a + b = ";
  cout << a + b;
  cout << "Complexo c: ";
  cout << c;
  cout << a.getNorm() << "\n";

  return 0;
}
