
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

  double a, b;
  int N = 10;
  double integral_rectangulo, integral_trapezio;
  
  cout << "Funções disponíveis - Código a introduzir " << endl;
  cout << " 1) sin(x) - 1 \n" <<  " 2) cos(x) - 2 \n" << " 3) exp(x) - 3 \n" << " 4) id(x) - 4 \n" << " 5) x² - 5 \n"<< endl;
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
    case 4:
      func = &iden;
      break;
    case 5:
      func = &quadra;
      break;
      
    }

  cout << "Introduza os extremos do intervalo " << endl;
  cin >> a >> b;

  integral_rectangulo = integra_rect(a, b, N, func);
  integral_trapezio = integra_trap(a, b, N, func);

  cout << "O integral definido de " << a << " até " << b << " da função escolhida é " << integral_rectangulo << " utilizando a aproximação por retângulos." << endl;

  cout << "O integral definido de " << a << " até " << b << " da função escolhida é " << integral_trapezio << " utilizando a aproximação por trapézios." << endl;

  
  /*cout << "Introduza um x inicial: " << endl;
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
  */
  
  return 0;
}
