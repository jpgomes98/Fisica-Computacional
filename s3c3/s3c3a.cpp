#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

double OH_Dx (double v)
{
  return v; 
}

double OH_Dv (double x, double v, double w0, double lbd)
{
  return -(pow(w0, 2) * x + (2 * lbd) * v);
}


void OH_RungeKutta(double x0, double v0, double w0, double lbd, double h, double tf)
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
      k2_x = v1 + (0.5) * h * k1_x;
      k3_x = v1 + (0.5) * h * k2_x;
      k4_x = v1 + h * k3_x;

      k1_v = OH_Dv(x1, v1, w0, lbd);
      k2_v = OH_Dv(x1 + (0.5) * h * k1_x, v1 + (0.5) * h * k1_v, w0, lbd);
      k3_v = OH_Dv(x1 + (0.5) * h * k2_x, v1 + (0.5) * h * k2_v, w0, lbd);
      k4_v = OH_Dv(x1 + (0.5) * h * k3_x, v1 + h * k3_v, w0, lbd);
      

      x2 = x1 + (h/6.) * (k1_x + 2 * k2_x + 2 * k3_x + k4_x);
      v2 = v1 + (h/6.) * (k1_v + 2 * k2_v + 2 * k3_v + k4_v);

      outKutta << t << " " << x1 << " " << v1 << endl;
      cout << t << " " << x1 << " " << v1 << endl; 
      
      x1 = x2;
      v1 = v2;
      t += h;
    }
}

void OH_Euler(double x0, double v0, double w0, double lbd, double h, double tf)
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
      
      outEuler << t << " " << x1 << " " << v1  << endl;

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

  double h = 0.01;
  double tf;

  cout << "*** Bem-vindo ao simulador do Oscilador Harmónico ***\n" << endl;
  cout << "Introduza k, m, b" << endl;
  cin >> k;
  cin >> m;
  cin >> b;

  cout << "Introduza as condiçõe iniciais (x0 e v0 por esta ordem)" << endl;
  cin >> x0;
  cin >> v0;

  cout << "Introduza o instante final da simulação" << endl;
  cin >> tf;
  
  w0 = sqrt(k / m);
  lbd = b / (2. * m);

  OH_Euler(x0, v0, w0, lbd, h, tf);
  OH_RungeKutta(x0, v0, w0, lbd, h, tf);

  return 0;
  
}
