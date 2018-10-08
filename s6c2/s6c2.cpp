#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <complex>
#include "Complex.h"

using namespace std;

int main()
{
  Complex a(2, 3);
  Complex b(5, 7);
  Complex aux(b.getNorm(), 0);

  complex<double> testSTL(2, 3);
  complex<double> toOperate(3, 7);
  
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

  /* Testar a biblioteca STL */
  cout << "*** Teste da biblioteca STL ***\n\n";
  cout << "Complexo testSTL: " << testSTL << endl;
  cout << "Complexo toOperate: " << toOperate << "\n" << endl;
  cout << "Soma dos dois = " << testSTL + toOperate << endl;
  cout << "Conjugado de testSTL: " << conj(testSTL) << endl;
  cout << "Argumento de testSTL: " << arg(testSTL) << "\n" << endl;

  cout << "*** Teste de operações com complexos ***\n\n";
  cout << "1) a + b = " << a + b << "\n" << endl;
  cout << "2) a - b = " << a - b << "\n" << endl;
  cout << "3) a * b = " << a * b << "\n" << endl;
  cout << "4) a / b = " << a / b << "\n" << endl;
  cout << "5) (a * conj(b))/|b|² = " << (a * b.conj()) / (aux * aux) << "\n" << endl;
  cout << "6) a = b? : " << (a == b) << "\n" << endl;
  cout << "7) a != b? : " << (a != b) << "\n" << endl;

  return 0;
}
