#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "Matrix.h"

#define THRESHOLD 1e-8

using namespace std;

/* Construtores*/

Matrix::Matrix(size_t ncol, size_t nlin): n(ncol), m(nlin) {
  
  mat = new double*[m];
  for (int i = 0; i < m; i++)
    {
      mat[i] = new double[n];
    }
}

Matrix::Matrix(const Matrix& M)
{
  n = M.n;
  m = M.m;

  mat = new double*[m];
  for (int i = 0; i < m; i++)
    {
      mat[i] = new double[n];
    }

  for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
	{
	  mat[i][j] = M.mat[i][j];
	}
    }
}

/* Destrutor */

Matrix::~Matrix()
{
  for (int i = 0; i < m; i++)
    {
      delete[] mat[i];
    }
  delete[] mat;
}

/* Funções */

void Matrix::set(unsigned i, unsigned j, double a)
{
  if (((i-1) >= m) || ((j-1) >= n) || ((i-1) < 0) || ((j-1) < 0))
    {
      cout << "A matriz em questão não tem esse elemento." << endl;
      cout << "Tente novamente" << endl;
      exit(EXIT_FAILURE);
    }
  else
    {
      mat[i-1][j-1] = a;
    }
}

size_t Matrix::ncol() const {return n;}
size_t Matrix::nlin() const {return m;}

void Matrix::resize(unsigned new_n, unsigned new_m)
{
  for (int i = 0; i < m; i++){
    delete[] mat[i];}
  delete[] mat;
  n = new_n;
  m = new_m;
  mat = new double*[m];
  for (int i = 0; i < m; i++)
    {
      mat[i] = new double[n];
    }
}

Matrix Matrix::inverse()
{
  double c = 0;
  double det = 1;
  
  if (n != m){
    cout << "A matrix não é quadrada, não é invertível!" << endl;
    exit(EXIT_FAILURE);
  }
  else{
    /* Definir a identidade */
    Matrix Id(n, m);
    Id = 0;
    for (int i = 0; i < Id.nlin(); i++){
      Id.mat[i][i] = 1;
    }
    /* Eliminação de Gauss */
    /* Obter matriz em escada de linhas */
    Matrix T(*this);
    for (int i = 0; i < (T.m - 1) ; i++){                    // linha atual que está a ser usada para eliminar
      for (int k = (i + 1); k < T.m; k++){                   // percorrer as linhas seguintes àquela que foi está selecionada
	if (T.mat[i][i] == 0){                               //  Verificar se o rank = nº colunas 
	  cout << "Pivot nulo encontrado! A matrix não é invertível." << endl;
	  cout << "O determinante desta matriz é nulo" << endl;
	  cout << "ERRO, interrompendo o processo de cálculo..." << endl;
	  det = 0;
	  return *this;
	}
	else {
	  c = ((double) T.mat[k][i]) / ((double) T.mat[i][i]); // coeficiente de eliminação
	  for (int j = 0; j < T.n; j++){
	    T.mat[k][j] = T.mat[k][j] - c * T.mat[i][j];       // percorrer a linha a subtrair a atual multiplicada por um fator c
	    Id.mat[k][j] = Id.mat[k][j] - c * Id.mat[i][j];    // primeiros coeficientes da inversa
	    /* DEBUGGING */
	    /*cout << "Passos Intermédios para encontrar Id:" << endl;
	      cout << Id << T; // CHECK*/
	  }
	}
      }
    }

    /* Calcular o determinante */

    for (int i = 0; i < T.m; i++){
      det *= T.mat[i][i];
    }
    
    /* Obter matriz diagonal */
    for (int i = (T.m - 1); i > 0; i--){
      for (int k = (i - 1); k >= 0; k--){
	c = ((double) T.mat[k][i]) / ((double) T.mat[i][i]);
	for(int j = (T.m - 1); j >= 0; j--){
	  T.mat[k][j] = T.mat[k][j] - c * T.mat[i][j];       // percorrer a linha a subtrair a atual multiplicada por um fator c
	  Id.mat[k][j] = Id.mat[k][j] - c * Id.mat[i][j];    // primeiros coeficientes da inversa
	  /* DEBUGGING */
	  /*cout << "Passos Intermédios para encontrar Id:" << endl;
	    cout << Id << T;*/
	}
      }
    }
    /* Obter matrix identidade */
    for (int i = 0; i < T.m; i++)
      {
	c = (1. / (double) (T.mat[i][i]));
	T.mat[i][i] *= c;
	for (int j = 0; j < T.n; j++){
	  Id.mat[i][j] *= c;
	  /* DEBUGGING */
	  /*cout << "Passos Intermédios para encontrar Id:" << endl;
	    cout << Id << T;*/
	}
      }
    cout << "\n";
    cout << "O determinante da matriz original é " << det << endl;
    cout << "det != 0. Inversão de matrix possível e completa." << endl;
    cout << "\n";
    return Id;
  }
}

/* Overload de Operadores */

Matrix& Matrix::operator=(const Matrix& M)
{
  if (this == &M){
    return *this;
  }
  else{
    if ((m != M.m) || (n != M.n))
      {
	this->resize(M.n, M.m);
      }
    for (int i = 0; i < m; i++){
      for (int j = 0; j < n; j++){
	mat[i][j] = M.mat[i][j];
      }
    }
    return *this;
  }
}

Matrix& Matrix::operator=(double a)
{
  for (int i = 0; i < m; i++){
    for (int j = 0; j < n; j++){
      mat[i][j] = a;
    }
  }

  return *this;
}

Matrix Matrix::operator+(const Matrix& M)
{
  if ((n == M.n) && (m == M.m)){
    Matrix result(n, m); // A matriz resultante tem o número de colunas da 2º e o número de linhas da 1º
    result = 0;
    for (int i = 0; i < result.m; i++){
      for (int j = 0; j < result.n; j++){
	result.mat[i][j] = mat[i][j] + M.mat[i][j];
      }
    }
    return result;
  }
  else{
    cout << "Matrizes não somáveis!" << endl;
    exit(EXIT_FAILURE);
  }
}

Matrix Matrix::operator*(const Matrix& M)
{
  /* Multiplicação legal? */
  if (n == M.m){
    Matrix result(M.n, m); // A matriz resultante tem o número de colunas da 2º e o número de linhas da 1º
    result = 0;
    for (int i = 0; i < result.m; i++){
      for (int j = 0; j < result.n; j++){
	for (int k = 0; k < n; k++){
	  result.mat[i][j] += mat[i][k] * M.mat[k][j]; 
	}
      }
    }
    
    return result;
  }

  else{
    cout << "Multiplicação ilegal. A dimensão das matrizes não permite multiplicação!" << endl;
    exit(EXIT_FAILURE);
  }
  
}

double Matrix::operator()(unsigned i, unsigned j) const
{
   if (((i-1) >= m) || ((j-1) >= n) || ((i-1) < 0) || ((j-1) < 0))
    {
      cout << "A matriz em questão não tem esse elemento." << endl;
      cout << "Não foi possível aceder ao valor dessa casa" << endl;
      exit(EXIT_FAILURE);
    }
   else{
     return mat[i-1][j-1];
   }
}
double& Matrix::operator()(unsigned i, unsigned j)
{
  if (((i-1) >= m) || ((j-1) >= n) || ((i-1) < 0) || ((j-1) < 0))
    {
      cout << "A matriz em questão não tem esse elemento." << endl;
      cout << "Não foi possível aceder ao valor dessa casa" << endl;
      exit(EXIT_FAILURE);
    }
   else{
     return mat[i-1][j-1];
   }
}

ostream& operator<<(ostream& out, const Matrix & r ) {
  cout << endl;
  for( unsigned i = 1; i <= r.nlin(); ++i ){
    for (unsigned j = 1; j <= r.ncol(); ++j)
      {
	if (abs(r(i,j)) <= THRESHOLD){ // controlo de precisão
	  out << 0 << " ";
	}
	else {
	  out << r(i,j) << " ";
	}
      }
    out << "\n";
  }
  cout << endl;
  return out;
}

Matrix solve(Matrix& A, const Matrix& b) {
  if (A.ncol() != A.nlin()){
    cout << "O sistema representado pela matriz em questão não tem característica máxima. Procure resolver a equação por outro método" << endl;
    exit(EXIT_FAILURE);
  }
  else if (A.ncol() != b.nlin()){
    cout << "O sistema representado pela matriz em questão não tem característica máxima. Procure resolver a equação por outro método" << endl;
    cout << "Neste caso, o vetor b tem um número de coeficientes difrente do número de linhas da matriz A" << endl;
    exit(EXIT_FAILURE);
  }
  else{
    Matrix x(A.nlin(), b.ncol());
    x = A.inverse() * b;
    return x;
  }
}
   
