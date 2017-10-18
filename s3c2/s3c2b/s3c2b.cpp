<<<<<<< HEAD

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

  

  
=======
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

void RungeKutta(double N1, double h, double tf, double lbd)
{
  double k1, k2, k3, k4;
  double t=0;
  double N2;
  
  ofstream outKutta ("Kutta.dat");
  
  while( t <= tf)
    {
      k1 = -lbd*N1;
      k2 = -(lbd*N1 + 0.5*h*k1);
      k3 = -(lbd*N1 + 0.5*h*k2);
      k4 = -(lbd*N1 + h*k3);  

      N2 = N1 + (double)(h/6)*(k1 +2*k2 + 2*k3 + k4);

      outKutta << t << " " << N1 << " " << endl;

      N1=N2;
      t += h;
    }
}

void Euler(double N1, double h, double tf, double lbd)
{
  double t=0;
  double N2;

  ofstream outEuler ("Euler.dat");
  
  while(t<=tf)
    {
      N2= N1 - lbd*N1*h;

      outEuler<< t << " " << N1 << " " << endl;

      N1 = N2;
      t += h;
    }
}

int main() 
{ 
  double N0, N1, tf, lbd;
  double h=0.3;

  cout << "Insira os valores da constante de decaimento " << endl;
  cin >> lbd;
  cout << "Introduza o valor inicial de N" << endl;
  cin >> N0;
  cout << "Introduza o tempo final" << endl;
  cin >> tf;

  N1=N0;
  
  Euler(N1, h, tf, lbd);
  RungeKutta(N1, h, tf, lbd);

  return 0;

>>>>>>> 55f16a3262993c538dcf43fd72ec53948876f8f3
}
