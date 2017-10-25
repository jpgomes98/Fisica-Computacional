#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>

#define GNUPLOT "gnuplot gnuplot_oscilador"

using namespace std;

/* Solução analítica para o MHS */

double Analitica (double x0, double w0, double t)
{
  return x0 * cos(w0*t);
}

/* Método Numerov */

void Numerov (double x0, double v0, double tf, double w0, double h)
{
  int c = 0;
  double t = 0;
  double x1, x2, x3, w0sqr;
  
  ofstream outNumerov("Oscilador_Numerov.dat");

  /* Para comparação dos métodos com a solução analítica */
  ofstream outAnalitica("Solucao_Analitica.dat");

  w0sqr = w0 * w0;
  
  x1 = x0;

  while( t <= tf)
    {
      
      if (c == 0)
	{
	  x2 = x0 * (1 + w0sqr * (h * h)/3.) + h * v0;
	  x2 /= 1 - (w0sqr * (h * h)/6.);
	}

      x3 = 2 * x2 * (1 - w0sqr * (5 * h * h)/12.) - x1 * (1 + w0sqr * (h * h)/12.);
      x3 /= (1 + w0sqr * (h * h)/12.);

      outNumerov << t << " " << x1 << " " << endl;
      outAnalitica << t << " " << Analitica(x0, w0, t) << " " << endl;
      
      x1 = x2;
      x2 = x3;
      t += h;
      c = 1;
    }
  
  c = 0;
}

/* Funções utilizadas no método de Euler e Runge-Kutta relativas ao movimento harmónico */

double OH_Dx (double v)
{
  return v; 
}

double OH_Dv (double x, double v, double w0, double lbd)
{
  return -w0 * w0 * x - 2 * lbd * v;
}
/***************************/

/* Método Runge-Kutta generalizado */

void RungeKutta(double x0, double v0, double w0, double lbd, double h, double tf)
{
  double k1_x, k2_x, k3_x, k4_x;
  double k1_v, k2_v, k3_v, k4_v;
  double t = 0;
  double x1 = 0, x2 = 0;
  double v1 = 0, v2 = 0;

  v1 = v0;
  x1 = x0;
  
  
  ofstream outKutta("Oscilador_Kutta.dat");
  
  while( t <= tf)
    {

      /* Cálculo dos declives do método Runge-Kutta */
      
      k1_x = v1;
      k1_v = OH_Dv(x1, v1, w0, lbd);
      
      k2_x = v1 + (0.5) * h * k1_v;
      k2_v = OH_Dv(x1 + (0.5) * h * k1_x, v1 + (0.5) * h * k1_v, w0, lbd);
      
      k3_x = v1 + (0.5) * h * k2_v;
      k3_v = OH_Dv(x1 + (0.5) * h * k2_x, v1 + (0.5) * h * k2_v, w0, lbd);
      
      k4_x = v1 + h * k3_v;
      k4_v = OH_Dv(x1 + h * k3_x, v1 + h * k3_v, w0, lbd);


      x2 = x1 + (h/6.) * (k1_x + 2 * k2_x + 2 * k3_x + k4_x);
      v2 = v1 + (h/6.) * (k1_v + 2 * k2_v + 2 * k3_v + k4_v);

      outKutta << t << " " << x1 << " " << v1 << endl;
      
      x1 = x2;
      v1 = v2;
      t += h;
    }
}

/* Método Euler generalizado */

void Euler(double x0, double v0, double w0, double lbd, double h, double tf)
{
  double t = 0;
  double x1 = 0, x2 = 0;
  double v1 = 0, v2 = 0;

  ofstream outEuler("Oscilador_Euler.dat");

  v1 = v0;
  x1 = x0;
  
  while(t <= tf)
    {
      v2 = v1 + h * OH_Dv(x1, v1, w0, lbd);
      x2 = x1 + h * v1;
      
      outEuler << t << " " << x1 << " " << v1 << endl;

      v1 = v2;
      x1 = x2;
      t += h;
    }
}

int main()
{ 
  double k, m, b;
  double x0, v0;

  double w0, lbd;
  double h = 0.1;
  double tf;

  int opt;

  /* Inicialização das variáveis */

  cout << "\x1b[1;31m" << "*** Bem-vindo à máquina dos seus sonhos ***\n" << endl;

  cout << "\x1b[1;32m" << "Indique que EDO pretende resolver (introduza os números identificadores)\n" << endl;

  cout << "\x1b[37m" << "   (1) Movimento Harmónico Simples \n   (2) Movimento Oscilatório Amortecido \n\n" << endl;
  cin >> opt;

  if (opt == 1)
    {
      cout << "\x1b[1;31m" << "Introduza k, m \x1b[37m" << endl;
      cin >> k;
      cin >> m;
    }
  else if (opt == 2)
    {
      cout << "\x1b[1;31m" << "Introduza k, m e b \x1b[37m" << endl;
      cin >> k;
      cin >> m;
      cin >> b;
    }
  else
    {
      cout << "Opção inválida" << endl;
      return 1;
    }
 
  cout << endl;
  
  cout << "\x1b[1;31m" << "Introduza as condições iniciais (x0 e v0 por esta ordem)\x1b[37m" << endl;
  cin >> x0;
  cin >> v0;

  cout << "\x1b[1;31m" << "Introduza o instante final da simulação \x1b[37m" << endl;
  cin >> tf;
  
  w0 = sqrt(k / m);

  if (opt == 1) // Oscilador Harmónico Simples (Numerov só aplicável aqui)
    {
      lbd = 0;
      Euler(x0, v0, w0, lbd, h, tf);
      RungeKutta(x0, v0, w0, lbd, h, tf);
      Numerov(x0, v0, tf, w0, h);
      system(GNUPLOT); /* Observar todos os gráficos no final */
    }

  else if (opt == 2) // Oscilador Harmónico Amortecido
    {
      lbd = b / (2. * m);
      Euler(x0, v0, w0, lbd, h, tf);
      RungeKutta(x0, v0, w0, lbd, h, tf);
    }
  

  return 0;
  
}
