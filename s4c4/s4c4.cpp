#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

/* Caso particular Eq. Poisson, D = 1*/

double norma (double *A, int n)
{
  double y = 0;
  for (int i = 0; i < n; i++)
    {
      y += A[i] * A[i];
    }

  return sqrt(y);
}

double chargeDens (double x) // função densidade de carga
{
  return 0;
}

double poisson_1d (double u0, double u2, double h, double a, int nmax)
{
  double u1 = 0;
  u1 = (u2 + u0)/(2.) + (h * h * chargeDens(a + h * nmax))/ (2.);
  return u1;
}

int main ()
{
  //int nmax = 10000;
  int npos = 500;
  double a, b;
  double Ua, Ub;
  double U[npos], V[npos];
  double h;
  double x;

  int j = 1, w = 1, it = 0;
  double tol = 10;

  ofstream output ("Poisson_1d.dat");

  cout << "Especifique as posições fronteira do problema a, b:" << endl;
  cin >> a;
  cin >> b;

  cout << "Especifique as condições fronteira do problema (U(a) e U(b)): " << endl;
  cin >> Ua;
  cin >> Ub;

  h =  ((b - a)/ (double) (npos));
  U[0] = Ua;
  U[npos - 1] = Ub;
  V[0] = Ua;
  V[npos - 1] = Ub;

  for (int i = 1; i < (npos - 1); i++)
    {
      U[i] = 0;
      V[i] = 0;
    }
  
  while (tol >= 1e-6)
    { 
      for (w = 0; w < npos; w++) // colocar na iterada seguinte os valores do vetor anterior num outro para comparar
	{
	  V[w] = U[w]; 
	}
      for (j = 1; j < (npos - 1); j++) // calcular o novo campo
	{
	  U[j] = poisson_1d(U[j-1], U[j+1], h, a, npos);
	}
      j = 1;
      w = 0;
      tol = abs(norma(U, npos) - norma(V, npos));
      it++; 
      // cout << tol << endl;
    }
  
  x = a;

  /* Obtenção dos dados após it iteradas */

  for (int i = 0; i < npos; i++)
    {
      output << x << " " << U[i] << endl;
      cout << x << " " << U[i] << endl;
      x += h;
    }

  cout << "Obteve-se a melhor solução para a eq. de Poisson após " << it << " iteradas." << endl;

  return 0;
}
