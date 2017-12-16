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

  /* Friends */
  friend ostream& operator<<(ostream& out, const Complex& z);
  
};

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

int main()
{
  Complex a(2, 3);
  Complex b(5, 7);
  Complex aux(b.getNorm(), 0);
  
  cout << "Complexo a: " << endl;
  cout << a << endl;
  cout << "Complexo b: " << endl;
  cout << b << endl;
  cout << "Novo complexo b: " << endl;
  b(1, 4);
  aux(b.getNorm(), 0);
  cout << b << endl;
  cout << "Norma de a: " << a.getNorm() << endl;
  cout << "Conjugado de a: " << a.conj() << "\n" << endl;

  cout << "*** Teste de operações com complexos ***\n\n";
  cout << "1) a + b = " << a + b << "\n" << endl;
  cout << "2) a - b = " << a - b << "\n" << endl;
  cout << "3) a * b = " << a * b << "\n" << endl;
  cout << "4) a / b = " << a / b << "\n" << endl;
  cout << "5) (a * conj(b))/|b|² = " << (a * b.conj()) / (aux * aux) << endl;

  return 0;
}
