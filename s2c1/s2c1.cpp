
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

/* Funções disponíveis */

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
  
int main()
{
  ofstream output("output.dat");
  
  double **mat;
  int n_i, n_j;
  n_j = 2;
  
  int f_user;
  double (*func)(double x);
  double x0, x_max, x;

  double step = 0.1;

  
  cout << " Funções disponíveis - Código a introduzir " << endl;
  cout << "1) sin(x) - 1 \n" <<  "2) cos(x) - 2 \n" << "3) exp(x) - 3 \n" << endl;
  cin >> f_user;

  switch(f_user)
    {
    case 1:
      func = &seno;
      break;
    case 2:
      func = &coss;
      break;
    case 3:
      func = &expo;
      break;
      
    }

  cout << "Introduza um x inicial: " << endl;
  cin >> x0;
  
  //cout << (*func)(x0) << endl;

  cout << "x máximo: " << endl;
  cin >> x_max;

  n_i = (int)((x_max - x0)/step);

  mat = new(nothrow) double*[n_i];
  if(!(mat))
    {
      cout << "Erro na alocação!" << endl;
      return 1;
    }

  for (int i = 0; i < n_i; i++)
    {
      mat[i] = new double[n_j];
      if(!(mat[i]))
	{
	  cout << "Erro na alocação!" << endl;
	  return 1;
	}
    }
  x = x0;

  for (int i = 0; i < n_i; i++)
    {
      mat[i][0] = x;
      mat[i][1] = (*func)(x);
      x += step;
    }

  for (int i = 0; i < n_i; i++)
    {
      for (int j = 0; j < n_j; j++)
	{
	  cout << " " << mat[i][j];
	  output << mat[i][j] << " ";
	}
      cout << "\n";
      output << "\n";
    }

  // DESALOCAR
  
  for (int i = 0; i < n_i; i++) delete[] mat[i];
  delete[] mat;
  
  return 0;
}
