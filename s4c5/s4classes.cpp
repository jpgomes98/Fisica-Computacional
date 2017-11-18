#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

#define GNUPLOT "gnuplot gnuplot_surface.plt"

using namespace std;

/* Introduzir classes neste exercício */

class Space{
  
  /* Tamanho do espaço gerado - 2D */
  size_t npos;
  /* Percorrer o espaço */
  double h[2];
  double x, y;
  /* Posições das cargas */
  double ch1[2];
  double ch2[2];
  /* Valor das cargas */
  double q;
  double eps0;
  
public:
  double **U, **V;
  explicit Space(size_t n); // construtor
  ~Space(); // destrutor

  /* Métodos */
  
  void setup(double Ux_a1, double Ux_a2, double Uy_b1, double Uy_b2);
  void equi_referencial(double a1, double a2, double b1, double b2);
  size_t size() const;
  void print(double a1, double b1, ofstream& out);

  /* Funções de resolução da Eq. Diferencial Parcial */
  
  double chargeDens();
  double poisson_2d (double u_x0, double u_x2, double u_y0, double u_y2, double a1, double b1, int i, int j);

  /* Amizades */
  
  friend double normaV (double *A, int n);

};

Space::Space(size_t n): npos(n)
{
  
  U = new double*[npos];
  V = new double*[npos];
  
  q = 0;
  eps0 = 8.854e-12;

  for (int i = 0; i < npos; i++)
    {
      U[i] = new double[npos];
      V[i] = new double[npos];
    }
  ch1[0] = 30;
  ch1[1] = 30;
  ch2[0] = 10;
  ch2[1] = 10;

}

Space::~Space()
{
  for (int i = 0; i < npos; i++)
    {
      delete U[i];
      delete V[i];
    }
  
  delete[] U;
  delete[] V;
  
  cout << "Os objetos da classe foram eliminados" << endl;
}

void Space::setup(double Ux_a1, double Ux_a2, double Uy_b1, double Uy_b2)
{
  int j = 1, i = 1;
  
  /* Potencial na fronteira */
  /* Ao longo de x */

  for (int v = 0; v < npos; v++)
    {
      U[v][0] = Uy_b1;
      U[v][npos - 1] = Uy_b2;
      V[v][0] = Uy_b1;
      V[v][npos - 1] = Uy_b2;
    }

  /* Ao longo de y, sem incluir as posições extremas */

  for (int v = 1; v < (npos - 1); v++)
    {
      U[0][v] = Ux_a1;
      U[npos - 1][v] = Ux_a2;
      V[0][v] = Ux_a1;
      V[npos - 1][v] = Ux_a2;
    }
  
  /* Inicialização das configurações */
  
  for (i = 1; i < (npos - 1); i++)
    {
      for (j = 1; j < (npos - 1); j++)
	{
	  U[i][j] = 0;
	  V[i][j] = 0;
	}
      j = 1;
    }
}

size_t Space::size() const
{
  return npos;
}

void Space::equi_referencial(double a1, double a2, double b1, double b2)
{
  /* Definir o step em X e em Y*/
  h[0] =  ((a2 - a1)/ (double) (npos));
  h[1] = ((b2 - b1)/(double) (npos));
}

void Space::print(double a1, double b1, ofstream& out)
{
   /* Obtenção dos dados após it iteradas */
  for (int k = 0; k < npos; k++)
    {
      for (int w = 0; w < npos; w++)
	{
	  x = a1 + k * h[0];
	  y = b1 + w * h[1];
	  out << x << " " << y << " " << U[k][w] << endl;
	  cout << x << " " << y << " " << U[k][w] << endl;
	}
    }
}

double normaV (double *A, int n) // norma vetorial
{
  double s = 0;
  for (int i = 0; i < n; i++)
    {
      s += A[i] * A[i];
    }

  return sqrt(s);
}

/* Método Numérico */

double Space::chargeDens() // função densidade de carga
{
  double r1 = sqrt((x - ch1[0]) * (x - ch1[0]) + (y - ch1[1]) * (y - ch1[1]));
  double r2 = sqrt((x - ch2[0]) * (x - ch2[0]) + (y - ch2[1]) * (y - ch2[1]));

  if (r1 <= 0.2)
    {
      q = 2;
    }
  else if (r2 <= 0.2)
    {
      q = -2;
    }
  else
    {
      q = 0;
    }

  return q;
}


double Space::poisson_2d (double u_x0, double u_x2, double u_y0, double u_y2, double a1, double b1, int i, int j)
{
  
  x = a1 + h[0] * i;
  y =  b1 + h[1] * j;
  
  double u1 = 0;
  
  u1 = (u_x0 + u_x2 + u_y0 + u_y2)/(4.) + /*((normaV(h, 2) * normaV(h, 2)) **/ chargeDens()/(eps0 * 4.);
  return u1;
}


int main ()
{
  Space Potencial(100);
  /* Definir as fronteiras */
  double a1, a2, b1, b2;
  double Ux_a1, Ux_a2, Uy_b1, Uy_b2;
  int it = 0, i = 1, j = 1;
  double tol = 10;

  ofstream output ("Poisson_2d_charge.dat"); 

  cout << "Especifique as posições dos vértices diagonais do quadrilátero (a1, b1) e (a2, b2):" << endl;
  cin >> a1;
  cin >> b1;
  cin >> a2;
  cin >> b2;

  if ((a2 < a1) || (b2 < b1))
    {
      cout << "Região não aceitável. a2 > a1 e b2 > b1." << endl;
      return 1;
    }

  cout << "Especifique o potencial na fronteira (Ux_a1, Ux_a2, Uy_b1, Uy_b2): " << endl;
  cin >> Ux_a1;
  cin >> Ux_a2;
  cin >> Uy_b1;
  cin >> Uy_b2;

  Potencial.setup(Ux_a1, Ux_a2, Uy_b1, Uy_b2);
  Potencial.equi_referencial(a1, a2, b1, b2);

  while (tol > 1e-9)
    {
      for (i = 1; i < (Potencial.size() - 1); i++)
	{
	  for (j = 1; j < (Potencial.size() - 1); j++) // calcular o novo campo
	    {
	      Potencial.U[i][j] = Potencial.poisson_2d(Potencial.U[i-1][j], Potencial.U[i+1][j], Potencial.U[i][j-1], Potencial.U[i][j+1], a1, b1, i, j);
	      tol = abs(Potencial.U[i][j] - Potencial.V[i][j]);
	      Potencial.V[i][j] = Potencial.U[i][j];
	    }
	}
      
      i = 1;
      j = 1;
      it++; 
    }

  Potencial.print(a1, b1, output);
  cout << "Obteve-se a melhor solução para a eq. de Poisson (2D) após " << it << " iteradas." << endl;

  output.close();
  system(GNUPLOT);

  return 0;
}
