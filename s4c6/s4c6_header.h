#ifndef S4C6_HEADER_H
#define S4C6_HEADER_H

using namespace std;

/* 3D */

class Space{
  /* Especificar o número de dimensões pretendido */
  int ndim;
  /* Tamanho do espaço gerado */
  size_t npos;
  /* Percorrer o espaço */
  double h2D[2];
  double h3D[3];
  double x, y, z;
  /* Posições das cargas */
  double ch1[3];
  double ch2[3];
  /* Valor das cargas */
  double q;
  double eps0;
  
public:
  double **U2, **V2;
  double ***U3, ***V3;
  explicit Space(size_t n, int N); // construtor
  ~Space(); // destrutor

  /* Métodos */
  
  void setup(double Ux_a1, double Ux_a2, double Uy_b1, double Uy_b2, double Uz_c1, double Uz_c2);
  void equi_referencial(double a1, double a2, double b1, double b2, double c1, double c2);
  size_t size() const;
  void print(double a1, double b1, double c1, ofstream& out);

  /* Funções de resolução da Eq. Diferencial Parcial */
  
  double chargeDens();
  double poisson_2d (double u_x0, double u_x2, double u_y0, double u_y2, double a1, double b1, int i, int j);
  double poisson_3d (double u_x0, double u_x2, double u_y0, double u_y2, double u_z0, double u_z2,  double a1, double b1, double c1, int i, int j, int k);

  /* Amizades */
  
  friend double normaV (double *A, int n);

};

double normaV (double *A, int n); // norma vetorial



#endif
