#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "Complex.h"

using namespace std;


/* Construtores */

Complex::Complex()
{
  Re = 0;
  Im = 0;
  norm = 0;
}

Complex::Complex(double x, double y)
{
  Re = x;
  Im = y;
  norm = sqrt(x * x + y * y);
}

Complex::Complex(const Complex& z)
{
  Re = z.Re;
  Im = z.Im;
  norm = z.norm;
}

double Complex::getNorm() const
{
  return sqrt(Re*Re + Im*Im);
}

double Complex::printRe() const
{
  return Re;
}

double Complex::printIm() const
{
  return Im;
}

Complex Complex::conj()
{
  Complex res(*this);
  res.Im = -Im;
  return res;
}

void Complex::operator()(double x, double y)
{
  Re = x;
  Im = y;
  norm = sqrt(x * x + y * y);
}

Complex& Complex::operator=(const Complex& z)
{
  Re = z.Re;
  Im = z.Im;

  return (*this);
}

Complex& Complex::operator=(const double a)
{
  Re = a;
  Im = 0;

  return (*this);
}


Complex Complex::operator+(const Complex& z)
{
  Complex res;

  res.Re = Re + z.Re;
  res.Im = Im + z.Im;

  return res;
}

Complex Complex::operator+(const double a)
{
  Complex res;

  res.Re = Re + a;
  res.Im = Im;

  return res;
}

Complex Complex::operator-(const Complex& z)
{
  Complex res;
  res.Re = Re - z.Re;
  res.Im = Im - z.Im;
  return res;
}

Complex Complex::operator-(const double a)
{
  Complex res;
  res.Re = Re - a;
  res.Im = Im;
  return res;
}


Complex Complex::operator*(const Complex& z)
{
  Complex res;
  res.Re = (Re * z.Re - Im * z.Im);
  res.Im = (z.Re * Im + Re * z.Im);

  return res;
}

Complex Complex::operator*(const double a)
{
  Complex res;
  res.Re = Re * a;
  res.Im = Im * a;

  return res;
}


Complex Complex::operator/(const Complex& z)
{
  Complex res;
  res.Re = (Re * z.Re + Im * z.Im) / (z.getNorm() * z.getNorm());
  res.Im = (z.Re * Im - Re * z.Im) / (z.getNorm() * z.getNorm());

  return res;
}

Complex Complex::operator/(const double a)
{
  Complex res;
  res.Re = Re / a;
  res.Im = Im / a;

  return res;
}


bool Complex::operator==(const Complex& z)
{
  if((Re == z.Re) && (Im == z.Im)){
    return true;
  }

  else{
    return false;
  }
}

bool Complex::operator!=(const Complex& z)
{
  if((Re == z.Re) && (Im == z.Im)){
    return false;
  }

  else{
    return true;
  }
}

/* Overloads definidos como friends */

ostream& operator<<(ostream& out, const Complex& z)
{
  if (z.printIm() >= 0){
    out << z.printRe() << "+" << z.printIm() << "i";
  }
  else{
    out << z.printRe() << "-" << (-1) * z.printIm() << "i";
  }

  return out;
}

/* Métodos úteis */

void printToFile(Complex** phi, double dx, double dy, int nx, int ny, double xmin, double ymin, ostream& out)
{
  for (int i = 0; i < nx; i++){
    for (int j = 0; j < ny; j++){
      out << (xmin + i * dx) << " " << (ymin + j * dy) << " " << phi[i][j].getNorm() << "\n";
    }
  }
}

void normalize(Complex **&phi, int nx, int ny, double dx, double dy)
{
  Complex integral;

  /* Calcular o integral que dará a constante de normalização */
  
  for (int i = 1; i < (nx - 1); i++){
    for (int j = 1; j < (ny - 1); j++){
      /* Tomar o valor médio da função num quadrado dx*dy */
      integral = integral + (phi[i][j].conj() * phi[i][j]) * (dx * dy);
    }
  }
  
  /* Dividir por sqrt(N) */
  
  for (int i = 1; i < (nx-1); i++){
    for (int j = 1; j < (ny-1); j++){
      phi[i][j] = (phi[i][j] / sqrt(integral.printRe()));
    }
  }
}

void swapSpace(Complex **&phi2, Complex **&phi1, int nx, int ny)
{
   for (int i = 0; i < nx; i++){
    for (int j = 0; j < ny; j++){
      phi1[i][j] = phi2[i][j];
    }
  }

}

/* Calcular o valor da função de phi para um certo phi, num dado ponto do espaço */

Complex funcGP(Complex& cur_phi, Complex& lap, Complex& dPhidx, Complex& dPhidy, double x, double y, double gamma, double omega, double G)
{
  Complex funcval;
  Complex imag(0, 1);
  
  funcval = lap * (-0.5) + cur_phi * (0.5 * (x*x + y*y) + G * (cur_phi.getNorm()) * (cur_phi.getNorm())) - (imag * omega) + dPhidy * x - dPhidx * y;
  
  return (funcval/(imag - gamma));
}

/* Calcular o lado direito da eq. de G-P */

void spaceGP(Complex **&func, Complex **&phi, double xmin, double ymin, double dx, double dy, int nx, int ny, double gamma, double omega, double G)
{
  /* Auxiliar */
  Complex lap;    // laplaciano
  Complex dPhidx; // derivada ao longo de x
  Complex dPhidy; // derivada ao longo de y
  Complex imag(0,1);   // un. imaginária
  /* Posição atual */
  double x, y;

  /* Calcular as entradas de F(phi) - atenção que os valores na fronteira não interessam, na medida em que as fronteiras são fixas */
  for (int i = 1; i < (nx - 1); i++){
    for (int j = 1; j < (ny - 1); j++){
      x = xmin + i * dx;
      y = ymin + j * dy;
      lap = ((phi[i+1][j] - (phi[i][j] * 2.0) + phi[i-1][j])/(dx * dx) + (phi[i][j+1] - (phi[i][j] * 2.0) + phi[i][j-1])/(dy * dy));
      dPhidx = (phi[i+1][j] - phi[i-1][j])/(2 * dx);
      dPhidy = (phi[i][j+1] - phi[i][j-1])/(2 * dy);
      
      /* Calcular as entradas propriamente ditas de F(phi) */
      func[i][j] = funcGP(phi[i][j], lap, dPhidx, dPhidy, x, y, gamma, omega, G);
    }
  }
  
}

/* Passo temporal para resolução da eq. diferencial usando RK3 */

Complex timeGP(Complex **&phi, double xmin, double ymin, double dx, double dy, double dt, int i, int j, double gamma, double omega, double G)
{
  /* Auxiliar */
  Complex lap;    // laplaciano
  Complex dPhidx; // derivada ao longo de x
  Complex dPhidy; // derivada ao longo de y
  /* Posição atual */
  double x, y;
  

  /* Coeficientes para Runge-Kutta 3 */
  Complex k1, k2, k3;

  /* Recalcular alguns parâmetros numéricos */
  x = xmin + i * dx;
  y = ymin + j * dy;
  lap = ((phi[i+1][j] - (phi[i][j] * 2.0) + phi[i-1][j])/ (dx * dx) + (phi[i][j+1] - (phi[i][j] * 2.0) + phi[i][j-1])/(dy * dy));
  dPhidx = (phi[i+1][j] - phi[i-1][j])/(2 * dx);
  dPhidy = (phi[i][j+1] - phi[i][j-1])/(2 * dy);

  k1 = phi[i][j] + funcGP(phi[i][j], lap, dPhidx, dPhidy, x, y, gamma, omega, G) * dt;
  k2 = (phi[i][j] * 0.75) + k1 * 0.25 + (funcGP(k1, lap, dPhidx, dPhidy, x, y, gamma, omega, G) * (0.25 * dt));
  k3 = (phi[i][j] * (1./3)) + (k2 * (2./3)) + (funcGP(k2, lap, dPhidx, dPhidy, x, y, gamma, omega, G) * ((2./3) * dt));

  return k3;
}
