#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>

#define GNUPLOT__1 "gnuplot gnuplot_pendulo"

using namespace std;

double D_omega_0 (double theta0, double theta1, double omega0, double omega1)
{
  return (omega0 * omega0 * sin(theta1 - theta0) * cos(theta1 - theta0) + sin(theta1) * cos(theta1 - theta0) + omega1 * omega1 * sin(theta1 - theta0) - sin(theta0)) / (1 - pow(cos(theta1 - theta0), 2));
}

double D_omega_1 (double theta0, double theta1, double omega0, double omega1)
{
  return (-omega1 * omega1 * sin(theta1 - theta0) * cos(theta1 - theta0) + sin(theta0) * cos(theta1 - theta0) - omega0 * omega0 * sin(theta1 - theta0) - sin(theta1)) / (1 - pow(cos(theta1 - theta0), 2));
}

/* Função para implementar Runge-Kutta */

double RK_pendulum (double h, double tf, double* theta_ini, double* omega_ini)
{
  double t = 0;
  double k1_w0, k2_w0, k3_w0, k4_w0;
  double k1_t0, k2_t0, k3_t0, k4_t0;

  double k1_w1, k2_w1, k3_w1, k4_w1;
  double k1_t1, k2_t1, k3_t1, k4_t1;

  double theta0, theta1;
  double omega0, omega1;

  double x0, x1;
  double y0, y1;
  
  theta0 = theta_ini[0];
  theta1 = theta_ini[1];

  omega0 = omega_ini[0];
  omega1 = omega_ini[1];

  ofstream pendulum0("pendulum0.dat");
  ofstream pendulum1("pendulum1.dat");

  while (t <= tf)
    {
      /* Calcular os coeficientes RK4 */

      /* K1 */

      k1_t0 = omega0;
      k1_w0 = D_omega_0(theta0, theta1, omega0, omega1);
      
      k1_t1 = omega1;
      k1_w1 = D_omega_1(theta0, theta1, omega0, omega1);

      /* K2 */
      
      k2_t0 = omega0 + 0.5 * h * k1_w0;
      k2_w0 = D_omega_0(theta0 + 0.5 * h * k1_t0, theta1 + 0.5 * h * k1_t1, omega0 + 0.5 * h * k1_w0, omega1 + 0.5 * h * k1_w1);

      k2_t1 = omega1 + 0.5 * h * k1_w1;
      k2_w1 = D_omega_1(theta0 + 0.5 * h * k1_t0, theta1 + 0.5 * h * k1_t1, omega0 + 0.5 * h * k1_w0, omega1 + 0.5 * h * k1_w1);

      /* K3 */
      
      k3_t0 = omega0 + 0.5 * h * k2_w0;
      k3_w0 = D_omega_0(theta0 + 0.5 * h * k2_t0, theta1 + 0.5 * h * k2_t1, omega0 + 0.5 * h * k2_w0, omega1 + 0.5 * h * k2_w1);

      k3_t1 = omega1 + 0.5 * h * k2_w1;
      k3_w1 = D_omega_1(theta0 + 0.5 * h * k2_t0, theta1 + 0.5 * h * k2_t1, omega0 + 0.5 * h * k2_w0, omega1 + 0.5 * h * k2_w1);

      /* K4 */
      
      k4_t0 = omega0 + h * k3_w0;
      k4_w0 = D_omega_0(theta0 + h * k3_t0, theta1 + h * k3_t1, omega0 + h * k3_w0, omega1 + h * k3_w1);

      k4_t1 = omega1 + h * k3_w1;
      k4_w1 = D_omega_1(theta0 + h * k3_t0, theta1 + h * k3_t1, omega0 + h * k3_w0, omega1 + h * k3_w1);

      /* Calcular os parâmetros seguintes */

      theta0 += (h/6.) * (k1_t0 + 2 * k2_t0 + 2 * k3_t0 + k4_t0);
      theta1 += (h/6.) * (k1_t1 + 2 * k2_t1 + 2 * k3_t1 + k4_t1);

      omega0 += (h/6.) * (k1_w0 + 2 * k2_w0 + 2 * k3_w0 + k4_w0);
      omega1 += (h/6.) * (k1_w1 + 2 * k2_w1 + 2 * k3_w1 + k4_w1);

      x0 = cos(theta0);
      y0 = sin(theta0);

      x1 = cos(theta1);
      y1 = sin(theta1);

      pendulum0 << t << " " << x0 << " " << y0 << endl;
      pendulum1 << t << " " << x1 << " " << y1 << endl;

      t += h;
    }
}

  
int main()
{
  double theta_ini[2];
  double omega_ini[2];
  double h;

  cout << "*** Duplo Pêndulo ***" << endl;
  cout << "Introduza as posições iniciais do 1º pêndulo e do 2º pêndulo" << endl;
  cin >> theta_ini[0];
  cin >> theta_ini[1];

  cout << "Introduza o step" << endl;
  cin >> h;

  omega_ini[0] = 0;
  omega_ini[1] = 1;

  RK_pendulum(h, 30, theta_ini, omega_ini);

  return 0;
}
