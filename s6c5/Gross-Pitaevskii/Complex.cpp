#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <string>
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

/* Operadores */

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

/* Rotinas úteis */
double Norm(const Complex& z)
{
  return sqrt(z.Re * z.Re + z.Im * z.Im);
}
double Re(const Complex& z)
{
  return z.Re;
}
double Im(const Complex& z)
{
  return z.Im;
}

/* Overloads definidos como friends */

/* Adição */
Complex operator+(const Complex& z, const Complex& w)
{
  Complex res;

  res.Re = w.Re + z.Re;
  res.Im = w.Im + z.Im;

  return res;
}
Complex operator+(const Complex& z, const double a)
{
  Complex res;

  res.Re = z.Re + a;
  res.Im = z.Im;

  return res;
}
Complex operator+(const double a, const Complex& z)
{
  Complex res;

  res.Re = z.Re + a;
  res.Im = z.Im;

  return res;
}

/* Subtração */
Complex operator-(const Complex& z, const Complex& w)
{
  Complex res;
  
  res.Re = z.Re - w.Re;
  res.Im = z.Im - w.Im;
  
  return res;
}
Complex operator-(const Complex& z, const double a)
{
  Complex res;
  
  res.Re = z.Re - a;
  res.Im = z.Im;
  
  return res;
}
Complex operator-(const double a, const Complex& z)
{
  Complex res;
  
  res.Re = a - z.Re;
  res.Im = (-1) * z.Im;
  
  return res;
}

/* Multiplicação */
Complex operator*(const Complex& z, const Complex& w)
{
  Complex res;
  
  res.Re = (z.Re * w.Re - z.Im * w.Im);
  res.Im = (w.Re * z.Im + z.Re * w.Im);

  return res;
}
Complex operator*(const Complex& z, const double a)
{
  Complex res;
  
  res.Re = z.Re * a;
  res.Im = z.Im * a;

  return res;
}
Complex operator*(const double a, const Complex& z)
{
  Complex res;
  
  res.Re = z.Re * a;
  res.Im = z.Im * a;

  return res;
}

/* Divisão */
Complex operator/(const Complex& z, const Complex& w)
{
  Complex res;
  res.Re = (z.Re * w.Re + z.Im * w.Im) / (Norm(w) * Norm(w));
  res.Im = (w.Re * z.Im - z.Re * w.Im) / (Norm(w) * Norm(w));

  return res;
}
Complex operator/(const Complex& z, const double a)
{
  Complex res;
  res.Re = z.Re / a;
  res.Im = z.Im / a;

  return res;
}
Complex operator/(const double a, const Complex& z)
{
  Complex res;
  Complex aux;
  
  aux = a;
  res = aux / z;
  
  return res;
}

/* Conjugar o complexo z */
Complex operator~(const Complex& z)
{
  Complex res(z);
  res.Im = -z.Im;
  return res;
}

/* Print */
ostream& operator<<(ostream& out, const Complex& z)
{
  if (Im(z) >= 0){
    out << z.Re << " + " << z.Im << "i";
  }
  else{
    out << z.Re << " - " << (-1) * z.Im << "i";
  }

  return out;
}


/********* Métodos para resolução da eq. Gross - Pitaevski *********/

/* Criar uma rede de pontos quadrada de lado 'size' e inicializar a 0s */
void CreateSquareGrid(Complex **&grid, int size)
{
  grid  = new Complex*[size];
  
  for (int i = 0; i < size; i++){
    grid[i]  = new Complex[size];
    for (int j = 0; j < size; j++){
      grid[i][j] = 0;
    }
  }
}

/* Eliminar as redes criadas */
void DestroyGrid(Complex **&grid, int size)
{
  for(int i = 0; i < size; i++){
    delete[] grid[i];
  }

  delete[] grid;
}

/* Definir os valores da fronteira (assumindo que são sempre os mesmos) */
void SetBoundaries(Complex **&grid, int size, Complex frontVal)
{
  /* Definir as fronteiras de y = const */
  for (int i = 0; i < size; i++){
    grid[i][0] = frontVal;
    grid[i][size - 1] = frontVal;
  }

  /* Definir as fronteiras de x = const */
  for (int i = 0; i < size; i++){
    grid[0][i] = frontVal;
    grid[size - 1][0] = frontVal;
  }
}

/* Definir os valores no interior */
void SetInside(Complex **&grid, int size, Complex intVal)
{
  for (int i = 1; i < (size - 1); i++){
    for (int j = 1; j < (size - 1); j++){
      grid[i][j] = intVal;
    }
  }
}

/* Rotina de impressão para um ficheiro */
void PrintToFile(Complex** phi, double h, int size, double xymin, ostream& out)
{
  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      out << (xymin + i * h) << " " << (xymin + j * h) << " " << Norm(phi[i][j]) * Norm(phi[i][j]) << "\n";
    }
    out << "\n"; // alteração no valor de x
  }
}

/* Integrar a função de onda atual e normalizar */
void Normalize(Complex **&phi, int size, double h)
{
  Complex integral;

  /* Calcular o integral que dará a constante de normalização */
  for (int i = 1; i < (size - 1); i++){
    for (int j = 1; j < (size - 1); j++){
      /* Tomar o valor médio da função num quadrado h*h */
      integral = integral + (~phi[i][j]) * phi[i][j] * (h * h);
    }
  }
  
  /* Dividir por sqrt(N) */
  for (int i = 1; i < (size - 1); i++){
    for (int j = 1; j < (size - 1); j++){
      phi[i][j] = (phi[i][j] / sqrt(Re(integral)));
    }
  }
}

void SwapSpace(Complex **&phi2, Complex **&phi1, int size)
{
   for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      phi1[i][j] = phi2[i][j];
    }
  }
}


/* Calcular o lado direito da eq. de G-P */
void ComputeFunction(Complex **&F, Complex **&phi, double xymin, double h, int size, double gamma, double omega, double G)
{
  /* Auxiliar */
  Complex lap;            // laplaciano
  Complex dPhidx;         // derivada ao longo de x
  Complex dPhidy;         // derivada ao longo de y
  Complex imag(0,1);      // un. imaginária
  
  /* Posição atual */
  double x, y;

  /* Calcular as entradas de F(phi) - atenção que os valores na fronteira não interessam, na medida em que as fronteiras são fixas */
  for (int i = 1; i < (size - 1); i++){
    for (int j = 1; j < (size - 1); j++){
      
      x = xymin + i * h;
      y = xymin + j * h;

      lap = ((phi[i+1][j] - (2.0 *phi[i][j]) + phi[i-1][j]) / (h * h)) + ((phi[i][j+1] - (2.0 * phi[i][j]) + phi[i][j-1]) / (h * h));
      dPhidx = (phi[i+1][j] - phi[i-1][j]) / (2 * h);
      dPhidy = (phi[i][j+1] - phi[i][j-1]) / (2 * h);
      
      /* Calcular o valor da função F(phi) para um certo phi, num dado ponto do espaço */
      
      F[i][j] = ((-0.5) * lap) + (0.5 * (x * x + y * y)) * phi[i][j] + (G * Norm(phi[i][j]) * Norm(phi[i][j])) * phi[i][j] - ((imag * omega) * (x * dPhidy - y * dPhidx)); 
      F[i][j] = F[i][j] / (imag - gamma);
    }
  }
}

/* Passo temporal para resolução da eq. diferencial usando RK3 */
void RefreshTime(Complex **&phi, Complex **&F, int size, double xymin, double h, double dt, double gamma, double omega, double G)
{
  /* Redes auxiliares para o cálculo das várias aproximações temporais seguintes com RK3  */
  
  Complex **grid1, **grid2;
  Complex **Func1, **Func2;

  CreateSquareGrid(grid1, size);
  CreateSquareGrid(grid2, size);

  /* Calcular k1 - 1º iteração temporal - Aprox. no final do intervalo [t, t+dt] */
  for (int i = 1; i < (size - 1); i++){
    for (int j = 1; j < (size - 1); j++){
      grid1[i][j] = phi[i][j] + F[i][j] * dt; 
    }
  }

  /* Calcular a rede de F para esta nova configuração - Func1 */
  CreateSquareGrid(Func1, size);
  ComputeFunction(Func1, grid1, xymin, h, size, gamma, omega, G);

  /* Calcular k2 - 2º iteração temporal */
  for (int i = 1; i < (size - 1); i++){
    for (int j = 1; j < (size - 1); j++){
      grid2[i][j] = (3.0 * phi[i][j] + grid1[i][j] + Func1[i][j] * dt) / (4.0); 
    }
  }

  /* Calcular a rede de F para a nova configuração agora gerada - Func2 */
  CreateSquareGrid(Func2, size);
  ComputeFunction(Func2, grid2, xymin, h, size, gamma, omega, G);

  /* Atualizar os valores da função de onda, phi, com base nos 'pesos' calculados anteriormente (RK3) */
  for (int i = 1; i < (size - 1); i++){
    for (int j = 1; j < (size - 1); j++){
      phi[i][j] = (phi[i][j] + 2.0 * grid2[i][j] + 2.0 * Func2[i][j] * dt) / (3.0); 
    }
  }

  /* Desalocar */
  DestroyGrid(grid1, size);
  DestroyGrid(grid2, size);
  DestroyGrid(Func1, size);
  DestroyGrid(Func2, size);
}
