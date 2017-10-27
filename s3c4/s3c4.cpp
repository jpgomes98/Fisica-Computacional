#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>

#define GNUPLOT__1 "gnuplot gnuplot_oscilador"
#define GNUPLOT__2 "gnuplot gnuplot_quantum"

using namespace std;

/* Funções utilizadas no método de RK4 para a Eq. Schrödinger */

double quantum_Dv (double x, double phi, double quantumK, double k, double E)
{
  return (1. / quantumK) * (E * phi - (k / 2.) * x * x * phi);
}

/* Funções utilizadas no método de Euler e Runge-Kutta relativas à Eq. do Movimento Harmónico Simples  */

double OH_Dx (double v)
{
  return v; 
}

double OH_Dv (double x, double v, double w0, double lbd)
{
  return -w0 * w0 * x - 2 * lbd * v;
}

/* RK4 para quãntica */

double quantumRungeKutta (double phi0, double dphi0, double quantumK, double k, double E, double xmax, double h, int checkE)
{
  double k1_p, k2_p, k3_p, k4_p;
  double k1_dp, k2_dp, k3_dp, k4_dp;
  double x = 0;
  
  double phi1 = 0, phi2 = 0;
  double dphi1 = 0, dphi2 = 0;

  dphi1 = dphi0;
  phi1 = phi0;
  
  
  ofstream outQKutta("quantumKutta.dat");
  
  while( x <= xmax)
    {

      /* Cálculo dos declives do método Runge-Kutta */
      
      k1_p = dphi1;
      k1_dp = quantum_Dv(x, phi1, quantumK, k, E);
      
      k2_p = dphi1 + (0.5) * h * k1_dp;
      k2_dp = quantum_Dv(x, phi1 + (0.5) * h * k1_p, quantumK, k, E);
      
      k3_p = dphi1 + (0.5) * h * k2_dp;
      k3_dp = quantum_Dv(x, phi1 + (0.5) * h * k2_p, quantumK, k, E);
      
      k4_p = dphi1 + h * k3_dp;
      k4_dp = quantum_Dv(x, phi1 + h * k3_p, quantumK, k, E);

      phi2 = phi1 + (h/6.) * (k1_p + 2 * k2_p + 2 * k3_p + k4_p);
      dphi2 = dphi1 + (h/6.) * (k1_dp + 2 * k2_dp + 2 * k3_dp + k4_dp);

      if (checkE == 1)
	{
	  outQKutta << x << " " << phi1 <<  endl;
	}
      
      phi1 = phi2;
      dphi1 = dphi2;
      x += h;
    }

  return phi2;
}



/***************************/

/* Método Numerov */

void Numerov (double x0, double v0, double tf, double w0, double h)
{
  int c = 0;
  double t = 0;
  double x1, x2, x3, w0sqr;
  
  ofstream outNumerov("Oscilador_Numerov.dat");

  /* Para comparação dos métodos com a solução analítica */
  //ofstream outAnalitica("Solucao_Analitica.dat");

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
      //outAnalitica << t << " " << Analitica(x0, w0, t) << " " << endl;
      
      x1 = x2;
      x2 = x3;
      t += h;
      c = 1;
    }
  
  c = 0;
}


/* Método Runge-Kutta  */

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

/* Método Euler */

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

double quantumBisect (double Ea, double Eb, double phi0, double dphi0, double quantumK, double k, double xmax, double h, double checkE)
{
  double ak;
  double bk;
  double xk;
  double f_a, f_b, f_x;
  double epsilon = 1e-12;

 
  for (int i = 0; i <= 100; i++)
    {
      ak = Ea + (double)i;
      bk = Eb + (double)i;

      f_a = quantumRungeKutta(phi0, dphi0, quantumK, k, Ea + (double)i, xmax, h, checkE);
      f_b = quantumRungeKutta(phi0, dphi0, quantumK, k, Eb + (double)i, xmax, h, checkE);

      if (f_a * f_b < 0)
	{
	  while ((bk - ak) > epsilon)
	    {
	      xk = (ak + bk)/2.;
	      f_a = quantumRungeKutta(phi0, dphi0, quantumK, k, ak, xmax, h, checkE);
	      f_x = quantumRungeKutta(phi0, dphi0, quantumK, k, xk, xmax, h, checkE);
	      if ((f_a * f_x) < 0)
		{
		  bk = xk;
		}
	      else
		{
		  ak = xk;
		}
	    }
	}
      else
	{
	  continue;
	}

      cout << "phi(7) = 0: E = " << xk << " " << endl; 
    }
  
  return xk;  
}

int main()
{ 
  double k, m, b;
  double x0, v0;

  double w0, lbd;
  double h;
  double tf;

  /* Schrödinger */
  double qM, h_reduzida, qK, quantumK;
  double phi0, dphi0;
  double xmax = 7;
  double E;
  double Ea, Eb;

  int opt;

  /* Inicialização das variáveis */

  /* Quântica */
  
  qK = 1;
  qM = 1;
  h_reduzida = 1;
  //E = 3./2.;
  

  cout << "\x1b[1;31m" << "*** Bem-vindo à máquina dos seus sonhos ***\n" << endl;

  cout << "\x1b[1;32m" << "Indique que EDO pretende resolver (introduza os números identificadores)\n" << endl;

  cout << "\x1b[37m" << "   (1) Movimento Harmónico Simples \n   (2) Movimento Oscilatório Amortecido \n   (3) Oscilador Quântico (Eq. Schrödinger) \n\n" << endl;
  cin >> opt;

  if (opt == 1)
    {
      cout << "\x1b[1;31m" << "Introduza k, m \x1b[37m" << endl;
      cin >> k;
      cin >> m;
      cout << "\x1b[1;31m" << "Introduza as condições iniciais (x0 e v0 por esta ordem)\x1b[37m" << endl;
      cin >> x0;
      cin >> v0;

      cout << "\x1b[1;31m" << "Introduza o instante final da simulação \x1b[37m" << endl;
      cin >> tf;
  
      w0 = sqrt(k / m);
    }
  else if (opt == 2)
    {
      cout << "\x1b[1;31m" << "Introduza k, m e b \x1b[37m" << endl;
      cin >> k;
      cin >> m;
      cin >> b;
      cout << "\x1b[1;31m" << "Introduza as condições iniciais (x0 e v0 por esta ordem)\x1b[37m" << endl;
      cin >> x0;
      cin >> v0;

      cout << "\x1b[1;31m" << "Introduza o instante final da simulação \x1b[37m" << endl;
      cin >> tf;
  
      w0 = sqrt(k / m);
    }
  else if (opt == 3)
    {
      cout << "\x1b[1;31m" << "Introduza as condições iniciais do oscilador quântico (phi0, dphi0)\x1b[37m" << endl;
      cin >> phi0;
      cin >> dphi0;
      cout << "\x1b[1;31mIntroduza o intervalo de shooting para a determinação da solução convergente da equação de Schrödinger (Ea, Eb)\x1b[37m" << endl;
      cin >> Ea;
      cin >> Eb;
    }
  else
    {
      cout << "Opção inválida" << endl;
      return 1;
    }
 
  cout << endl;

  cout << "\x1b[1;32mIntroduza o step iterativo (h) \n\n\x1b[37m" << endl;
  cin >> h;
 

  if (opt == 1) // Oscilador Harmónico Simples (Numerov só aplicável aqui)
    {
      w0 = sqrt(k / m);
      lbd = 0;
      Euler(x0, v0, w0, lbd, h, tf);
      RungeKutta(x0, v0, w0, lbd, h, tf);
      Numerov(x0, v0, tf, w0, h);
      system(GNUPLOT__1); /* Observar todos os gráficos no final */
    }

  else if (opt == 2) // Oscilador Harmónico Amortecido
    {
      w0 = sqrt(k / m);
      lbd = b / (2. * m);
      Euler(x0, v0, w0, lbd, h, tf);
      RungeKutta(x0, v0, w0, lbd, h, tf);
    }

  else if (opt == 3)
    {
      quantumK = -(h_reduzida * h_reduzida) / (2. * qM);
      E = quantumBisect (Ea, Eb, phi0, dphi0, quantumK, qK, xmax, h, 0);
      quantumRungeKutta(phi0, dphi0, quantumK, qK, E, xmax, h, 1);
      system(GNUPLOT__2);
    }
  

  return 0;
  
}
