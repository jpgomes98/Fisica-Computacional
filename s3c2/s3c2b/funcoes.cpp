#include <iostream>
#include <cmath>
#include <fstream>
#include "s3.h"

using namespace std;

double expon(double x)
{
  return exp(x);
}

double decaimentoDf (double x, double lbd)
{
  return (-lbd * x);
}

void analiticaDecaimento (double N0, double h, double tf, double lbd)
{
  ofstream analiticaOut("Analica_Decaimento.dat");
  double t = 0;
  double N;
  
  while( t <= tf)
    {
      N = N0 * expon(-lbd * t);
      analiticaOut << t << " " << N << endl;
      t += h;
    }
  
}

void RungeKutta(double N1, double h, double tf, double lbd)
{
  double k1, k2, k3, k4;
  double t = 0;
  double N2 = 0;

  k1 = 0;
  k2 = 0;
  k3 = 0;
  k4 = 0;
  
  ofstream outKutta("Kutta.dat");
  
  while( t <= tf)
    {
      k1 = decaimentoDf(N1, lbd);
      k2 = decaimentoDf(N1 + (0.5)*h*k1, lbd);
      k3 = decaimentoDf(N1 + (0.5)*h*k2, lbd);
      k4 = decaimentoDf(N1 + h*k3, lbd);  

      N2 = N1 + (h/6.) * (k1 + 2 * k2 + 2 * k3 + k4);
      cout << k1 << " " << k2 << " " << k3 << " " << k4 << endl;

      outKutta << t << " " << N1 << endl;
      
      
      N1 = N2;
      t += h;
    }
}

void Euler(double N1, double h, double tf, double lbd)
{
  double t=0;
  double N2;

  ofstream outEuler("Euler.dat");
  
  while(t<=tf)
    {
      N2= N1 - lbd*N1*h;

      outEuler<< t << " " << N1 << " " << endl;

      N1 = N2;
      t += h;
    }
}


