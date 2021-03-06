#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include "s2_header.h"

using namespace std;


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
