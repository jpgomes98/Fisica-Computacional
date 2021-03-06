
#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include "s2_header.h"

using namespace std;
  
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
  int N;;
  double integral_rectangulo, integral_trapezio, integral_simpson;
  
  cout << "Funções disponíveis - Código a introduzir " << endl;
  cout << " 1) sin(x) - 1 \n" <<  " 2) cos(x) - 2 \n" << " 3) exp(x) - 3 \n" << " 4) id(x) - 4 \n" << " 5) x² - 5 \n\n" << " 6) Função de onda quântica - 6 \n\n"<< endl;
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
    case 6:
      func = &wavefunc;
      break;
    default:
      cout << " Função inexistente!" <<  endl;
      return 1;     
    }

  if (f_user == 6)
    {
      cout << "Introduza o extremo do intervalo. Deve ser elevado. " << endl;
      cin >> b;
      a = -b;

      cout << "Introduza o nº de subpartições do intervalo [-a, a] " << endl;
      cin >> N;

      integral_rectangulo = integra_rect(a, b, N, func);
      integral_trapezio = integra_trap(a, b, N, func);
      integral_simpson = integra_simp(a, b, N, func);

      cout << "O integral definido de " << a << " até " << b << " da função escolhida é " << integral_rectangulo << " utilizando a aproximação por retângulos." << endl;

      cout << "O integral definido de " << a << " até " << b << " da função escolhida é " << integral_trapezio << " utilizando a aproximação por trapézios." << endl;

      cout << "O integral definido de " << a << " até " << b << " da função escolhida é " << integral_simpson << " utilizando o Método de Simpson." << endl;
    }

  else
    {

      cout << "Introduza os extremos do intervalo " << endl;
      cin >> a >> b;

      cout << " Introduza o nº de subpartições do intervalo [a, b] " << endl;
      cin >> N;

      integral_rectangulo = integra_rect(a, b, N, func);
      integral_trapezio = integra_trap(a, b, N, func);
      integral_simpson = integra_simp(a, b, N, func);

      cout << "O integral definido de " << a << " até " << b << " da função escolhida é " << integral_rectangulo << " utilizando a aproximação por retângulos." << endl;

      cout << "O integral definido de " << a << " até " << b << " da função escolhida é " << integral_trapezio << " utilizando a aproximação por trapézios." << endl;

      cout << "O integral definido de " << a << " até " << b << " da função escolhida é " << integral_simpson << " utilizando o Método de Simpson." << endl;

    }
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
