#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

#define GNUPLOT "gnuplot gnuplot_surface.plt"

using namespace std;

/* Eq. Poisson, D = 2 / Com norma matricial e stop criterium FALTA */

double normaV (double *A, int n) // terá de ser uma norma vetorial
{
  double y = 0;
  for (int i = 0; i < n; i++)
    {
      y += A[i] * A[i];
    }

  return sqrt(y);
}

/*double normaM (double **A, int n)
{
  double y = 0;
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
	{
	  
	}
    }
    }*/

double chargeDens (double x, double y) // função densidade de carga
{
  /* Posições das cargas */
  double pos_ch1_x = 30;
  double pos_ch1_y = 30;
  double pos_ch2_x = 10;
  double pos_ch2_y = 10;
  double q = 0;
  
  double r1 = sqrt((x - pos_ch1_x) * (x - pos_ch1_x) + (y - pos_ch1_y) * (y - pos_ch1_y));
  double r2 =  sqrt((x - pos_ch2_x) * (x - pos_ch2_x) + (y - pos_ch2_y) * (y - pos_ch2_y));

  if (r1 <= 0.2)
    {
      q = 2;
    }
  else if (r2 <= 0.2)
    {
      q = -2;
    }
  else
    {
      q = 0;
    }

  return q;
}

double poisson_2d (double u_x0, double u_x2, double u_y0, double u_y2, double h[2], double a1, double b1, int i, int j)
{
  double u1 = 0;
  u1 = (u_x0 + u_x2 + u_y0 + u_y2)/(4.) - ((normaV(h, 2) * normaV(h, 2)) * chargeDens(a1 + h[0] * i, b1 + h[1] * j))/ (4.);
  return u1;
}

int main ()
{
  //int nmax = 10000;
  int npos = 40;
  
  double a1, a2, b1, b2;
  double Ux_a1, Ux_a2, Uy_b1, Uy_b2;
  double U[npos][npos], V[npos][npos];
  double h[2];
  double x, y;

  int i = 1, j = 1, it = 0;
  
  double tol = 10;

  ofstream output ("Poisson_2d_charge.dat");

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
  /* Ao longo de x */

  for (int v = 0; v < npos; v++)
    {
      U[v][0] = Uy_b1;
      U[v][npos - 1] = Uy_b2;
      V[v][0] = Uy_b1;
      V[v][npos - 1] = Uy_b2;
    }

  /* Ao longo de y */

  for (int v = 1; v < (npos - 1); v++)
    {
      U[0][v] = Ux_a1;
      U[npos - 1][v] = Ux_a2;
      V[0][v] = Ux_a1;
      V[npos - 1][v] = Ux_a2;

    }
  
  /* V[0] = Ua;
     V[npos - 1] = Ub;*/
  
  /* Setup das configurações */
  
  for (i = 1; i < (npos - 1); i++)
    {
      for (j = 1; j < (npos - 1); j++)
	{
	  U[i][j] = 0;
	  V[i][j] = 0;
	}
      j = 1;
    }

  i = 1;
  j = 1;

  
  while (tol > 1e-8)
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
	      tol = abs(U[i][j] - V[i][j]);
	      V[i][j] = U[i][j];
	    }
	}
      
      i = 1;
      j = 1;
      it++; 
      cout << tol << endl;
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

  cout << "Obteve-se a melhor solução para a eq. de Poisson (2D) após " << it << " iteradas." << endl;

  output.close();
  system(GNUPLOT);

  return 0;
}
