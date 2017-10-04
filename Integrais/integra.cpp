#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include "s2_header.h"

using namespace std;


double integra_rect(double a, double b, int N, double (*f)(double x))
{
  double dx = (double)((b - a)/N);
  double x1, x2, x_med, sum;
  
  sum = 0;
  x1 = a;
  
  for (int i = 0; i < N; i++)
    {
      x2 = x1 + dx;
      x_med = (x1 + x2)/2;
      sum += ((*f)(x_med)) * dx;
      x1 = x2;
    }

  return sum;
}

double integra_trap(double a, double b, int N, double (*f)(double x))
{
   double dx = (double)((b - a)/N);
   double x1, x2, sum;

   sum = 0;
   x1 = a;
    
  for (int i = 0; i < N; i++)
    {
      x2 = x1 + dx;
      sum += (((*f)(x1) + (*f)(x2))/2) * dx;
      x1 = x2;
    }

  return sum;
}

double integra_simp(double a, double b, int N, double (*f)(double x))
{
  double h, sum;
  double x_med;
  double x1, x2;
  
  /*if (N % 2 != 0)
    {
      cout << "Erro no Método de Simpson. N deve ser par!" << endl;
      exit(EXIT_FAILURE);
      }*/

  h = (double)((b - a)/N);
  x_med = a + (h/2.);
  sum = 0;
  x1 = a;
  x2 = a + h;

  for (int i = 1; i <= N; i++)
    {
      sum += ((*f)(x1) + 4 * (*f)(x_med) + (*f)(x2));
      x1 += h;
      x_med = x1 + (h/2.);
      x2 += h;
    }

  return ((sum * h) / 6.);
  

}
