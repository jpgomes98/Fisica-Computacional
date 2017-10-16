#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "s2_header.h"

using namespace std;

double dist(double *x_n, int dim)
{
  double d;

  for (int i = 0; i < dim; i++)
    {
      d += pow(x_n[i], 2);
    }

  return d;
}

double pdf(double x) // para já a única PDF disponível
{
  double y;
  y = (1/(sqrt(M_PI))) * exp(-pow(x, 2));

  return y;
}

double wavefunc(double x)  // alpha = 1, N = 1/(pow((M_PI), 1/4))
{
  double y;
  y = pow(x, 4) * (1/(sqrt(M_PI))) * exp(-pow(x, 2));
  
  return y;
}

double seno(double x)
{
  double y;
  y = sin(x);
  return y;
}

double coss(double x)
{
  double y;
  y = cos(x);
  return y;
}

double expo(double x)
{
  double y;
  y = exp(x);
  return y;
}

double iden(double x)
{
  double y;
  y = x;
  return y; 
}

double quadra(double x)
{
  double y;
  y = x*x;
  return y;
}


double quarta(double x)
{
  double y;
  
  y = quadra(x) * quadra(x);
  return y;
}
