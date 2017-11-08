#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

#define GNUPLOT "gnuplot gnuplot_config_4_3.plt"

using namespace std;

/* Eq. Disponíveis */

/* 1) f(x) = cos(x)^2 */

double f1 (double x)
{
  return cos(x) * cos(x);
}

/* Tentativa de implementar classes com métodos iterativos */

class Pfixo {
public:
  Pfixo();
  double x1;
  double x2;
  double (*f)(double);
  double w;
  void iter_relax(void);
};

/* Construtor */

Pfixo::Pfixo()
{
  x1 = 0;
  x2 = 0;
  w = 0.01;
  f = &f1;
}

void Pfixo::iter_relax()
{
  x2 = w * f(x1) + (1 - w) * x1;
}

int main ()
{
  Pfixo eq;
  double stop = 1e-6;
  int it = 0;
  double x0;

  /* Matriz com os valores de w pertencentes a [0,1] */
  double** otimiza;
  double step_w;
  int n_w;
  double new_w;
  int count;

  ofstream output("iteradas_w.dat");
   
  cout << "Introduza o valor inicial: " << endl;
  cin >> x0;

  cout << "Introduza o step de teste de valores do parâmetro w: " << endl;
  cin >> step_w;

  eq.w = step_w;
  n_w = 1./(step_w) - 1;

  otimiza = new double*[n_w];
  for (int i = 0; i < n_w; i++)
    {
      otimiza[i] = new double[2];
    }

  for (int i = 0; i < n_w; i++)
    {
      eq.x1 = x0;
      eq.x2 = 0;
      
      while(abs(eq.x2 - eq.x1) >= stop)
	{
	  eq.x1 = eq.x2;
	  eq.iter_relax();
	  it++;
	}
      cout << "w_" << i << " = " << it << " iteradas necessárias." << endl; 
      otimiza[i][0] = eq.w;
      otimiza[i][1] = it;
      eq.w += step_w;
      it = 0;
    }

  /* Imprimir para um ficheiro e determinar o valor de w que minimiza o número de iterações */
  
  new_w = eq.w; // por opção, preferiu-se começar com o último valor de w testado
  count = otimiza[n_w - 1][1]; // obter o nº de iteradas correspondente ao último valor de w
  
  for (int i = 0; i < n_w; i++)
    {
      output << otimiza[i][0] << " " << otimiza[i][1] << endl;
      if (otimiza[i][1] < count)
	{
	  new_w =  otimiza[i][0];
	  count = otimiza[i][1];
	}
    }

  
  cout << "A solução encontrada para a equação é: " << eq.x2 << endl;
  cout << "O valor de w que minimizou o número de iteradas foi: " << new_w << endl;
  cout << "Foram precisas " <<  count << " iteradas para obter a solução com esse valor de w." << endl;

  /* Desalocar a matriz e finalizar */
  
  for (int i = 0; i < 2; i++)
    {
      delete[] otimiza[i];
    }
  delete[] otimiza;
  output.close();
  system(GNUPLOT);

  return 0;
}
