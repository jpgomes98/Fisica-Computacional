#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "s2_header.h"

using namespace std;
  
int main()
{
  ofstream output("output.dat");
  ofstream markovOut("markov_chain.dat");

  /* s2c1 */
  
  double **mat;
  int n_i, n_j;
  n_j = 2;
  double step = 0.1;

  /**/
  
  int f_user;
  double (*func)(double x);
  double (*ro)(double x);
  double x0, x_max, x;


  double a, b;
  int N;
  double integral_rectangulo, integral_trapezio, integral_simpson;

  /*Metropolis Monte Carlo - v2*/

  double *confs_markov;
  int n_confs;
  int markovs;
  double r;

  double **matrix_MC;

  double integral_montecarlo;
  

  /* Random */

  srand(time(NULL));
  
  /**********/
  
  cout << "Funções disponíveis - Código a introduzir " << endl;
  cout << " 1) sin(x) - 1 \n" <<  " 2) cos(x) - 2 \n" << " 3) exp(x) - 3 \n" << " 4) id(x) - 4 \n" << " 5) x² - 5 \n" << " 6) Função de onda quântica - 6 \n" << " 7) Monte Carlo para uma certa PDF - 7 \n\n"<< endl;
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
    case 7:
      func = &quarta;
      ro = &pdf;
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
  
   else if (f_user == 7)
    {
      cout << "Introduza os extremo do intervalo " << endl;
      cin >> a;

      cout << "Introduza o nº de configurações a gerar: " << endl;
      cin >> n_confs;

      cout << "Introduza o nº de iteradas das cadeias de Markov: " << endl;
      cin >> markovs;

      cout << "Introduza o step aleatório: " << endl;
      cin >> r;
      cout << endl;

      /*Alocar*/

      matrix_MC = new(nothrow) double*[n_confs];
      if(!(matrix_MC))
	{
	  cout << "Erro na alocação!" << endl;
	  return 1;
	}

      for (int i = 0; i < n_confs; i++)
	{
	  matrix_MC[i] = new(nothrow) double[2];
	  if(!(matrix_MC[i]))
	    {
	      cout << "Erro na alocação!" << endl;
	      return 1;
	    }
	}


      confs_markov = markov(ro, a, n_confs, markovs, r);

      cout << " Estas são as configurações geradas: \n" << endl;

      for (int i = 0; i < n_confs; i++)
	{
	  cout << " " << confs_markov[i];
	  matrix_MC[i][0] = confs_markov[i];
	  if ((i % 5) == 0)
	    {
	      cout << endl;
	    }
	  markovOut << i << " " << confs_markov[i]  << endl; 
	}
      cout << endl;

      integral_montecarlo = integra_montecarlo(confs_markov, matrix_MC, n_confs, func);

      for (int i = 0; i < n_confs; i++)
	{
	  output << " " << matrix_MC[i][0] << " " << matrix_MC[i][1] << endl;
	}
      cout << "O integral definido de " << -a << " até " << a << " da função escolhida é " << integral_montecarlo << " utilizando o Método de Metropolis Monte Carlo." << endl;
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
  
  delete[] confs_markov;
  for (int i = 0; i < n_confs; i++) delete[] matrix_MC[i];
  delete[] matrix_MC;
  return 0;
}
