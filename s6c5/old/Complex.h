#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

class Complex{
  double Re;
  double Im;
  double norm;
public:
  Complex();
  Complex(double x, double y);
  Complex(const Complex& z);

  /* Rotinas úteis */
  double getNorm() const;
  double printRe() const;
  double printIm() const;
  Complex conj();

  /* Operadores para complexos - Complex - e escalares - doubles */
  void operator()(double x, double y);
  Complex& operator=(const Complex& z);
  Complex& operator=(const double a);
  Complex operator+(const Complex& z);
  Complex operator+(const double a);
  Complex operator-(const Complex& z);
  Complex operator-(const double a);
  Complex operator*(const Complex& z);
  Complex operator*(const double a);
  Complex operator/(const Complex& z);
  Complex operator/(const double a);

  
  /* Booleans */
  bool operator==(const Complex& z);
  bool operator!=(const Complex& z);

  /* Friends */
  friend ostream& operator<<(ostream& out, const Complex& z);
  
};

/* Métodos úteis */

void printToFile(Complex** phi, double dx, double dy, int nx, int ny, double xmin, double ymin, ostream& out);

/* Normalizar a função de onda 2D */
void normalize(Complex **&phi, int nx, int ny, double dx, double dy);

/* Atualizar o "espaço" */
void swapSpace(Complex **&phi2, Complex **&phi1, int nx, int ny);

/* Passos de cálculo numérico para resolver a eq. de G-P */

/* Função de definição do 2º membro da eq. de G-P */
Complex funcGP(Complex& cur_phi, Complex& lap, Complex& dPhidx, Complex& dPhidy, double x, double y, double gamma, double omega, double G);

/* Rotina de atualização do espaço a cada passo temporal */
void spaceGP(Complex **&func, Complex **&phi, double xmin, double ymin, double dx, double dy, int nx, int ny, double gamma, double omega, double G);

/* Passo temporal para resolução da eq. diferencial usando RK3 */
Complex timeGP(Complex **&phi, double xmin, double ymin, double dx, double dy, double dt, int i, int j, double gamma, double omega, double G);

#endif
