#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <complex>
#include <string>
#include "Complex.h"

using namespace std;

int main()
{
  Complex a(1, 1);
  Complex b(2, 4);
  double t = 2;

  cout << "*** Teste ***\n\n";
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  cout << "t = " << t << endl;
  cout << "a*b = " << a * b << endl;
  cout << "a/b = " << a/b << endl;
  cout << "a + t = " << a + t << endl;
  cout << "t + a = " << t + a << endl;
  cout << "t/b = " << t/b << endl;
  cout << "a - t = " << a - t << endl;
  cout << "t - a = " << t - a << endl;
  cout << "a * t = " << a * t << endl;
  cout << "Norma de a: " << Norm(a) << endl;
  cout << "Conj. de a: " << ~a << endl;
  cout << "a_bar * a: " << (~a) * a << endl;
  cout << "Re(a_nar * a) :" << Re((~a)*a) << endl;

  return 0;
}
