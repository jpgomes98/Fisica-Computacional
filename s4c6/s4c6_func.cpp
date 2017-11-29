#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "s4c6_header.h"

using namespace std;

Space::Space(size_t n, int N): npos(n), ndim(N)
{
  
  q = 0;
  eps0 = 8.854e-12;

  if (N == 2)
    {
      U2 = new double*[npos];
      V2 = new double*[npos];

      for (int i = 0; i < npos; i++)
	{
	  U2[i] = new double[npos];
	  V2[i] = new double[npos];
	}

    }

  if (N == 3)
    {
      U3 = new double**[npos];
      V3 = new double**[npos];

      for (int i = 0; i < npos; i++)
	{
	  U3[i] = new double*[npos];
	  V3[i] = new double*[npos];
	  for (int j = 0; j < npos; j++)
	    {
	      U3[i][j] = new double[npos];
	      V3[i][j] = new double[npos];
	    }
	}
    }


  
  ch1[0] = 3;
  ch1[1] = 3;
  ch1[2] = 3;
  ch2[0] = 6;
  ch2[1] = 6;
  ch2[2] = 6;

}

Space::~Space()
{
  if (ndim == 2)
    {
      for (int i = 0; i < npos; i++)
	{
	  delete[] U2[i];
	  delete[] V2[i];
	}
  
      delete[] U2;
      delete[] V2;
    }

  else if (ndim == 3)
    {
      for (int i = 0; i < 10; i++)
	{
	  for (int j = 0; j < 10; j++)
	    {
	      delete[] U3[i][j];
	      delete[] V3[i][j];
	    }
	  delete[] U3[i];
	  delete[] V3[i];
	}

      delete[] U3;
      delete[] V3;
    }
  
  cout << "Os objetos da classe foram eliminados" << endl;
}

void Space::setup(double Ux_a1, double Ux_a2, double Uy_b1, double Uy_b2, double Uz_c1, double Uz_c2)
{
  int j = 1, i = 1, k = 1;
  
  /* Potencial na fronteira */
  /* Ao longo de x */

  if (ndim == 2)
    {

      for (int v = 0; v < npos; v++)
	{
	  U2[v][0] = Uy_b1;
	  U2[v][npos - 1] = Uy_b2;
	  V2[v][0] = Uy_b1;
	  V2[v][npos - 1] = Uy_b2;
	}

      /* Ao longo de y, sem incluir as posições extremas */

      for (int v = 1; v < (npos - 1); v++)
	{
	  U2[0][v] = Ux_a1;
	  U2[npos - 1][v] = Ux_a2;
	  V2[0][v] = Ux_a1;
	  V2[npos - 1][v] = Ux_a2;
	}
  
      /* Inicialização das configurações */
  
      for (i = 1; i < (npos - 1); i++)
	{
	  for (j = 1; j < (npos - 1); j++)
	    {
	      U2[i][j] = 0;
	      V2[i][j] = 0;
	    }
	  j = 1;
	}
    }

  if (ndim == 3)
    {
      for (k = 1; k < (npos -1); k++)
	{
	  /* Ao longo de x */
	  for (int v = 0; v < npos; v++)
	    {
	      U3[v][0][k] = Uy_b1;
	      U3[v][npos - 1][k] = Uy_b2;
	      V3[v][0][k] = Uy_b1;
	      V3[v][npos - 1][k] = Uy_b2;
	    }

	  /* Ao longo de y, sem incluir as posições extremas */

	  for (int v = 1; v < (npos - 1); v++)
	    {
	      U3[0][v][k] = Ux_a1;
	      U3[npos - 1][v][k] = Ux_a2;
	      V3[0][v][k] = Ux_a1;
	      V3[npos - 1][v][k] = Ux_a2;
	    }
	}
      k = 1;

      /* Para z = 0 */
      for (int v = 0; v < npos; v++)
	{
	  for (int w = 0; w < npos; w++){
	    U3[v][w][0] = Uz_c1;
	  }
	}

      /* Para z = npos */
      for (int v = 0; v < npos; v++)
	{
	  for (int w = 0; w < npos; w++){
	    U3[v][w][npos] = Uz_c2;
	  }
	}
      
  
      /* Inicialização das configurações */
      for (k = 1; k < (npos - 1); k++)
	{
	  for (i = 1; i < (npos - 1); i++)
	    {
	      for (j = 1; j < (npos - 1); j++)
		{
		  U3[i][j][k] = 0;
		  V3[i][j][k] = 0;
		}
	      j = 1;
	    }
	  i = 1;
	}
    }
}

size_t Space::size() const
{
  return npos;
}

void Space::equi_referencial(double a1, double a2, double b1, double b2, double c1, double c2)
{
  /* Definir o step em X e em Y e em Z */

  if (ndim == 2)
    {
      h2D[0] = ((a2 - a1)/ (double) (npos));
      h2D[1] = ((b2 - b1)/(double) (npos));
    }
  else if (ndim == 3)
    {
      h3D[0] = ((a2 - a1)/ (double) (npos));
      h3D[1] = ((b2 - b1)/(double) (npos));
      h3D[2] = ((c2 - c1)/(double) (npos));
    }

}

void Space::print(double a1, double b1, double c1, ofstream& out)
{
   /* Obtenção dos dados após it iteradas */

  if (ndim == 2)
    {
      for (int k = 0; k < npos; k++)
	{
	  for (int w = 0; w < npos; w++)
	    {   
	      x = a1 + k * h2D[0];
	      y = b1 + w * h2D[1];
	      out << x << " " << y << " " << U2[k][w] << endl;
	      cout << x << " " << y << " " << U2[k][w] << endl;
	    }
	}
    }

  if (ndim == 3)
    {
      for (int d = 0; d < npos; d++)
	{
	  for (int k = 0; k < npos; k++)
	    {
	      for (int w = 0; w < npos; w++)
		{
		  x = a1 + k * h3D[0];
		  y = b1 + w * h3D[1];
		  z = c1 + d * h3D[2];
		  out << x << " " << y << " " << " " << z << " " << U3[k][w][d] << endl;
		  cout << x << " " << y << " " << " " << z << " " << U3[k][w][d] << endl;
		}
	    }
	}
    }
}

double normaV (double *A, int n) // norma vetorial
{
  double s = 0;
  for (int i = 0; i < n; i++)
    {
      s += A[i] * A[i];
    }

  return sqrt(s);
}


/* Método Numérico */

double Space::chargeDens() // função densidade de carga
{
  double r1 = 0, r2 = 0, r3 = 0;

  if (ndim == 2){
    
    r1 = sqrt((x - ch1[0]) * (x - ch1[0]) + (y - ch1[1]) * (y - ch1[1]));
    r2 = sqrt((x - ch2[0]) * (x - ch2[0]) + (y - ch2[1]) * (y - ch2[1]));

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
  }
  
  else if(ndim == 3){

    r1 = sqrt((x - ch1[0]) * (x - ch1[0]) + (y - ch1[1]) * (y - ch1[1]) + (z - ch1[2]) * (z - ch1[2]));
    r2 = sqrt((x - ch2[0]) * (x - ch2[0]) + (y - ch2[1]) * (y - ch2[1]) + (z - ch2[2]) * (z - ch2[2]));

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
  }

  return q;
}


double Space::poisson_2d (double u_x0, double u_x2, double u_y0, double u_y2, double a1, double b1, int i, int j)
{
  
  x = a1 + h2D[0] * i;
  y = b1 + h2D[1] * j;
  
  double u1 = 0;
  
  u1 = (u_x0 + u_x2 + u_y0 + u_y2)/(4.) + (normaV(h2D, 2) * normaV(h2D, 2)) * chargeDens()/(eps0 * 4.);
  return u1;
}

double Space::poisson_3d (double u_x0, double u_x2, double u_y0, double u_z0, double u_z2, double u_y2, double a1, double b1, double c1, int i, int j, int k)
{
  
  x = a1 + h3D[0] * i;
  y = b1 + h3D[1] * j;
  z = c1 + h3D[2] * k;
  
  double u1 = 0;
  
  u1 = (u_x0 + u_x2 + u_y0 + u_y2 + u_z0 + u_z2)/(6.) + (normaV(h3D, 3) * normaV(h3D, 3)) * chargeDens()/(eps0 * 4.);
  return u1;
}
