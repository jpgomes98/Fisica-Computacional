#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
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

double *markov(double (*pdf)(double x), double a, int n_conf, int m, double r)
{
  double *confs;
  double x;

  int i = 0, count = 0;
  double q0, q1;
  int last_q;
  
  double rand_step;
  double p_ratio;

  double al;

  srand(time(NULL));

  /**/

  confs = new double[n_conf];

  /**/

  /* Iniciar Markov */
  q0 = (((double)(rand())/(double)(RAND_MAX))) * (2 * a) - a;

  //cout << " Valor inicial (q0): " << q0  << endl;

  for (int j = 0; j < n_conf; j++)
    {
      while (i < m)
	{
	  rand_step =  (((double)(rand())/(double)(RAND_MAX))) * (2 * r) - r;

	  q1 = q0 + rand_step;
  
	  al = ((double)rand()/(double)(RAND_MAX));
	  p_ratio =  (((*pdf)(q1)) / ((*pdf)(q0)));

	  if (p_ratio > al)
	    {
	      q0 = q1;
	      count++;    
	    }
	  i++;
	}
      /*cout << " AL: " << al << endl; DEBUG
	cout << " Rand_step: " << rand_step << endl;*/
      cout << " Taxa de aceitação: " << (double)(count)/(double)(m) << endl;
      x = q0;
      confs[j] = x;
      i = 0;
      count = 0;
    }

  return confs;
}

double integra_montecarlo(double *confs, double **mat, int n, double (*f)(double x))
{
  double sum = 0;
  
  for (int i = 0; i < n; i++)
    {
      mat[i][1] = (*f)(confs[i]);
      sum += mat[i][1];
    }
  return sum / n;
}

void markov_Ndim(double (*pdf)(double x), double a, int n_conf, int m, double r, int dim, double **confs_vect)
{
  //double **confs;

  int i = 0, count = 0;
  double *q0;
  int componente;

  int rate_print;
  
  double rand_step;
  double p_ratio;

  double al;

  srand(time(NULL));

  ofstream out_2dim("2D_pointcloud.dat");

  /**/
  q0 = new double[dim];
  //q1 = new double[dim];
  //rand_step = new double[dim];

  /**/

  cout << " Imprimir taxa de aceitação? 1 - Sim / 0 - Não \n\n" <<endl;
  cin >> rate_print;

  /* Iniciar Markov */

  for (int i = 0; i < dim; i++)
    {
      q0[i] = (((double)(rand())/(double)(RAND_MAX))) * (2 * a) - a;
    }
  
  //cout << " Valor inicial (q0): " << q0  << endl;

  for (int j = 0; j < n_conf; j++)
    {
      while (i < m)
	{
	  rand_step =  (((double)(rand())/(double)(RAND_MAX))) * (2 * r) - r;

	  componente = rand() % dim;
	  
	  al = ((double)rand()/(double)(RAND_MAX));
	  p_ratio =  (((*pdf)(dist(q0, componente, rand_step, dim))) / ((*pdf)(dist(q0, -1, 0, dim))));
	  /*dist(q0, -1, 0, dim) corresponde a distãncia do vetor de componentes antes da adição do passo aleatório*/
	  
	  if (p_ratio > al)
	    {
	      q0[componente] += rand_step;;
	      count++;    
	    }
	  i++;
	}
      /*cout << " AL: " << al << endl; DEBUG
	cout << " Rand_step: " << rand_step << endl;*/

      if (rate_print == 1)
	{
	  cout << " Taxa de aceitação: " << (double)(count)/(double)(m) << endl;
	  cout << " Componente escolhida: " << componente << endl;
	}
      
      for (int w = 0; w < dim; w++)
	{
	  confs_vect[j][w] = q0[w];

	  /* Plot nuvem de pontos 2D */
	  if (dim == 2)
	    {
	      out_2dim << confs_vect[j][w] << " ";
	      if (w == 1)
		{
		  out_2dim << "\n";
		}
	    }
	}
      i = 0;
      count = 0;
    }

  delete[] q0;
  //delete[] q1;
  //delete[] rand_step;
}


double integra_montecarlo_Ndim (double **confs_vect, int n_confs, double (*f)(double x), int dim)
{
  double sum = 0;

  for (int i = 0; i < n_confs; i++)
    {
      sum += (*f)(dist(confs_vect[i], -1, 0, dim));
    }
  
  return (((double) sum) / ((double) n_confs));
}
