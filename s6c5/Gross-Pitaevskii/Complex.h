#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

class Complex{
  double Re;
  double Im;
  double norm;
public:
  Complex();
  Complex(double x, double y);
  Complex(const Complex& z);

  /* Operadores para atribuição de complexos - Complex - e escalares - doubles */
  /* Alterar os parâmetros do complexo */
  void operator()(double x, double y);
  /* Igualdade a complexos e escalares */
  Complex& operator=(const Complex& z);
  Complex& operator=(const double a);

  /* Booleans */
  bool operator==(const Complex& z);
  bool operator!=(const Complex& z);

  /* Friends para overload de operadores */
  /* Rotinas úteis */
  friend double Norm(const Complex& z);
  friend double Re(const Complex& z);
  friend double Im(const Complex& z);
  
  /* Adição */
  /* - complexos */
  friend Complex operator+(const Complex& z, const Complex& w);
  /* - escalares */
  friend Complex operator+(const Complex& z, const double a); // adição à direita
  friend Complex operator+(const double a, const Complex& z); // adição à esquerda

  /* Subtração */
  /* - complexos */
  friend Complex operator-(const Complex& z, const Complex& w);
  /* - escalares */
  friend Complex operator-(const Complex& z, const double a); // subtração à direita
  friend Complex operator-(const double a, const Complex& z); // subtração à esquerda

  /* Multiplicação */
  /* - complexos */
  friend Complex operator*(const Complex& z, const Complex& w);
  /* - escalares */
  friend Complex operator*(const Complex& z, const double a); // multiplicação à direita
  friend Complex operator*(const double a, const Complex& z); // multiplicação à esquerda

  /* Divisão */
  /* - complexos */
  friend Complex operator/(const Complex& z, const Complex& w);
  /* - escalares */
  friend Complex operator/(const Complex& z, const double a); // divisão à direita
  friend Complex operator/(const double a, const Complex& z); // divisão à esquerda

  /* Conjugado */
  friend Complex operator~(const Complex& z);
  
  /* Print */
  friend ostream& operator<<(ostream& out, const Complex& z);
  
};

/********* Métodos para resolução da eq. Gross - Pitaevski *********/
/* Criar uma rede de pontos quadrada de lado 'size' e inicializar a 0s */
void CreateSquareGrid(Complex **&grid, int size);

/* Eliminar as redes criadas */
void DestroyGrid(Complex **&grid, int size);

/* Definir os valores da fronteira (assumindo que são sempre os mesmos) */
void SetBoundaries(Complex **&grid, int size, Complex frontVal);

/* Definir os valores no interior */
void SetInside(Complex **&grid, int size, Complex intVal);

/* Rotina de impressão para um ficheiro */
void PrintToFile(Complex** phi, double step, int size, double xymin, ostream& out);

/* Integrar a função de onda atual e normalizar */
void Normalize(Complex **&phi, int size, double h);

/* Trocar */
void SwapSpace(Complex **&phi2, Complex **&phi1, int size);

/* Calcular o lado direito da eq. de G-P */
void ComputeFunction(Complex **&F, Complex **&phi, double xymin, double h, int size, double gamma, double omega, double G);

void RefreshTime(Complex **&phi, Complex **&F, int size, double xymin, double h, double dt, double gamma, double omega, double G);

#endif
