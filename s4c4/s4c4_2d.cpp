#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

#define GNUPLOT_ROT "gnuplot gnuplot_rotate_graph.plt"

using namespace std;

/* Eq. Poisson, D = 2*/

double norma (double *A, int n) // terá de ser uma norma matricial
{
  double y = 0;
  for (int i = 0; i < n; i++)
    {
      y += A[i] * A[i];
    }

  return sqrt(y);
}

double chargeDens (double x, double y) // função densidade de carga
{
  return sin(x * y);
}

double poisson_2d (double u_x0, double u_x2, double u_y0, double u_y2, double h[2], double a1, double b1, int i, int j)
{
  double u1 = 0;
  u1 = (u_x0 + u_x2 + u_y0 + u_y2)/(4.) - ((norma(h, 2) * norma(h, 2)) * chargeDens(a1 + h[0] * i, b1 + h[1] * j))/ (4.);
  return u1;
}

int main ()
{
  int nmax = 1000;
  int npos = 100;
  
  double a1, a2, b1, b2;
  double Ux_a1, Ux_a2, Uy_b1, Uy_b2;
  double U[npos][npos]; //, V[npos];
  double h[2];
  double x, y;

  int i = 1, j = 1, it = 0;
  
  //double tol = 10;

  ofstream output ("Poisson_2d.dat");

  cout << "Especifique as posições dos vértices diagonais do quadrilátero (a1, b1) e (a2, b2):" << endl;
  cin >> a1;
  cin >> b1;
  cin >> a2;
  cin >> b2;

  if ((a2 < a1) || (b2 < b1))
    {
      cout << "Região não aceitável. a2 > a1 e b2 > b1." << endl;
      return 1;
    }

  cout << "Especifique o potencial na fronteira (Ux_a1, Ux_a2, Uy_b1, Uy_b2): " << endl;
  cin >> Ux_a1;
  cin >> Ux_a2;
  cin >> Uy_b1;
  cin >> Uy_b2;

  /* Definir o step em X e em Y*/
  
  h[0] =  ((a2 - a1)/ (double) (npos));
  h[1] = ((b2 - b1)/(double) (npos));

  /* Potencial na fronteira */

  for (int v = 0; v < npos; v++)
    {
      U[v][0] = Uy_b1;
      U[v][npos - 1] = Uy_b2;
      U[0][v] = Ux_a1;
      U[npos - 1][v] = Ux_a2;
    }
  
  /* V[0] = Ua;
     V[npos - 1] = Ub;*/
  
  /* Setup das configurações */
  
  for (i = 1; i < (npos - 1); i++)
    {
      for (j = 1; j < (npos - 1); j++)
	{
	  U[i][j] = 0;
	}
      j = 1;
    }

  i = 1;
  j = 1;

  
  for (int u = 0; u < nmax; u++)
    {

      /* Calculos para a convergencia */
      /* for (w = 0; w < npos; w++) // colocar na iterada seguinte os valores do vetor anterior num outro para comparar
	 {
	 V[w] = U[w]; 
	 }*/
  
      for (i = 1; i < (npos - 1); i++)
	{
	  for (j = 1; j < (npos - 1); j++) // calcular o novo campo
	    {
	      U[i][j] = poisson_2d(U[i-1][j], U[i+1][j], U[i][j-1], U[i][j+1], h, a1, b1, i, j);
	    }
	}
      
      i = 1;
      j = 1;
      //tol = abs(norma(U, npos) - norma(V, npos));
      it++; 
      // cout << tol << endl;
    }
  
  x = a1;
  y = b1;

  /* Obtenção dos dados após it iteradas */

  for (int k = 0; k < npos; k++)
    {
      for (int w = 0; w < npos; w++)
	{
	  x = a1 + k * h[0];
	  y = b1 + w * h[1];
	  output << x << " " << y << " " << U[k][w] << endl;
	  cout << x << " " << y << " " << U[k][w] << endl;
	}
    }

  cout << "Obteve-se a melhor solução para a eq. de Poisson após " << it << " iteradas." << endl;

  system(GNUPLOT_ROT);

  return 0;
}
