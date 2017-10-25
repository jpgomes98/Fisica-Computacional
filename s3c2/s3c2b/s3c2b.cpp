

#include <iostream>
#include <cmath>
#include <fstream>
#include "s3.h"

using namespace std;

int main()
{

  /* Método de Euler para resolver dN/dt = -lbd * N */
  
  double N1, N2, N_0, dN;
  double h = 0.01;
  double t = 0, t_f;
  double lbd;
  int y_n;

  double (*f)(double x) = &expon;

  ofstream outEuler ("Euler.dat");
  ofstream outDecaimento ("Analica_Decaimento.dat");

  cout << "Insira os valores da constante de decaimento " << endl;
  cin >> lbd;

  cout << "Insira N0 " << endl;
  cin >> N_0;

  cout << "Insira t_final " << endl;
  cin >> t_f;

  cout << "Imprimir derivada? 1 ou 0" << endl;
  cin >> y_n;

  N1 = N_0;
  
  while (t <= t_f)
    {      
      N2 = N1 - lbd * N1 * h;
      if (y_n == 1)
	{
	  outEuler << t << " " << N1 << " " << (N2 - N1)/h << endl;
	}
      else
	{
	  outEuler << t << " " << N1 << " " << endl;
	}
      outDecaimento << t << " " << N_0 * (*f)(-(lbd * t)) << endl; 
      N1 = N2;
      t += h;
    }
  

  return 0;

  
}
