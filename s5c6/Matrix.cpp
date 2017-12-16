#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <ctime>
#include "dirent.h"
#include "Matrix.h"

#define THRESHOLD 1e-12

using namespace std;

/* Construtores*/

Matrix::Matrix(size_t ncol, size_t nlin): n(ncol), m(nlin) {
  
  mat = new double*[m];
  for (int i = 0; i < m; i++)
    {
      mat[i] = new double[n];
    }
  det = 1; // Até ser calculado, ficará assim
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

  det = M.det;
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

void Matrix::vec_in(unsigned j, const Matrix& v_in)
{
  if ((j < 1) || (j > n)){
    cout << "A matriz em questão não tem esse elemento." << endl;
    cout << "Tente novamente" << endl;
    exit(EXIT_FAILURE);
  }
  else if ((v_in.ncol() != 1) || (v_in.nlin() > m)){
    cout << "Vetor de dimensões não compatíveis para juntar à matriz." << endl;
    cout << "Só são aceites vetores coluna" << endl;
    exit(EXIT_FAILURE);
  }
  else{
    for (int i = 1; i <= m; i++){
      mat[i-1][j-1] = v_in(i, 1);
    }
  }
}

Matrix Matrix::vec_out(unsigned j) const
{
  Matrix v(1, m);
  for (int i = 1; i <= v.nlin(); i++){
    v.set(i, 1, (*this)(i, j));
  }

  return v;
}

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

double Matrix::findDet()
{
  /* Cálculo do determinante pelo Método de Eliminação de Gauss */
  /* Obter matriz em escada de linhas */

  if(n != m){
    cout << "A matriz tem dimensões " << m << "x" << n << ". Não é quadrada, pelo que não tem determinante definido!" << endl;
    det = nan("");
  }

  else{
    Matrix T(*this); // tabalhar com uma cópia
    double c = 1;
  
    for (int i = 0; i < (T.m - 1) ; i++){                    // linha atual que está a ser usada para eliminar
      for (int k = (i + 1); k < T.m; k++){                   // percorrer as linhas seguintes àquela que foi está selecionada
	if (T.mat[i][i] == 0){                               //  Verificar se o rank = nº colunas 
	  det = 0;
	}
	else {
	  c = ((double) T.mat[k][i]) / ((double) T.mat[i][i]); // coeficiente de eliminação
	  for (int j = 0; j < T.n; j++){
	    T.mat[k][j] = T.mat[k][j] - c * T.mat[i][j];
	    // percorrer a linha a subtrair a atual multiplicada por um fator c
	  }
	}
      }
    }

    /* Calcular o determinante */

    for (int i = 0; i < T.m; i++){
      det *= T.mat[i][i];
    }
  }
  return det;
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

Matrix Matrix::transpose() const
{
  Matrix T(*this);
  if (n != m){
    T.resize(m, n);
  }
  for (int i = 1; i <= T.nlin(); i++){
    for (int j = 1; j <= T.ncol(); j++){
      T.set(i, j, mat[j - 1][i - 1]);
    }
  }

  return T;
}

Matrix& Matrix::normalize()
{
  double norm = dot((*this),(*this));
  
  for (int i = 0; i < m; i++){
    for (int j = 0; j < n; j++){
      mat[i][j] /= sqrt(norm);
    }
  }

  return *this;
}

Matrix Matrix::bigEigenvec(const Matrix& ini_guess)
{
  double eigen = 0;
  //double eigen2 = 0;
  double eps = 1e-9;
  double dif = 10;
  int i = 1;
  Matrix V1(ini_guess);
  Matrix V2(ini_guess.n, ini_guess.m);
  

  while(abs(dif) >= eps){
    V2 = (*this) * V1;
    eigen = (V2(ini_guess.m, 1)) / (V1(ini_guess.m, 1));
    V2 = V2.normalize();
    dif = V2(ini_guess.m, 1) - V1(ini_guess.m, 1);
    V1 = V2;
    i++;
  }

  return V2;
}

bool Matrix::isSymmetric()
{
  int check = 0;
  
  if(n != m){
    cout << "A matriz não é quadrada => não é simétrica." << endl;
    check = 1;
  }

  else{
    Matrix Copy(n, m);
    Copy = this->transpose();
    
    for(int i = 0; i < m; i++){
      for(int j = 0; j < n; j++){
	if ((i != j) && ((mat[i][j]- Copy.mat[i][j]) > 1e-10)){
	  check = 1;
	  break;
	}
      }
    }
  }

  if (check == 1){
    return false;
  }
  else{
    return true;
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

Matrix Matrix::operator-(const Matrix& M)
{
  if ((n == M.n) && (m == M.m)){
    Matrix result(n, m); // A matriz resultante tem o número de colunas da 2º e o número de linhas da 1º
    result = 0;
    for (int i = 0; i < result.m; i++){
      for (int j = 0; j < result.n; j++){
	result.mat[i][j] = mat[i][j] - M.mat[i][j];
      }
    }
    return result;
  }
  else{
    cout << "Matrizes não subtraíveis!" << endl;
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

Matrix operator*(double a, const Matrix& M)
{
  Matrix Ret(M); //matrix de retorno
  for (int i = 0; i < M.m; i++){
    for (int j = 0; j < M.n; j++){
      Ret.mat[i][j] *= a;
    }
  }

  return Ret;
}

Matrix operator/(const Matrix& M, double a)
{
  Matrix Ret(M); //matrix de retorno
  for (int i = 0; i < M.m; i++){
    for (int j = 0; j < M.n; j++){
      Ret.mat[i][j] /= a;
    }
  }

  return Ret;
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
    cout << "Neste caso, o vetor b tem um número de coeficientes diferente do número de linhas da matriz A" << endl;
    exit(EXIT_FAILURE);
  }
  else{
    Matrix x(A.nlin(), b.ncol());
    x = A.inverse() * b;
    return x;
  }
}

double dot(const Matrix& A, const Matrix& B){
  // Testar se são vetores
  double val = 0;
  int a = 0, b = 0;
  /* Matrizes de correção - podem ter qualquer dimensão */
  Matrix At(1, 1);
  Matrix Bt(1, 1);
  if (((A.nlin() > 1) && (A.ncol() > 1)) || (((B.nlin() > 1) && (B.ncol() > 1)))){
      cout << "Os objetos apresentados não são vetores. O produto interno não está definido." << endl;
      val = nan("");
  }
  else{
    /*cout << "Check! Os objetos em questão são vetores. Verificando se é possível aplicar o produto interno..." << endl;*/

    if (((A.nlin() == B.nlin()) || (A.ncol() == B.ncol()))){
      /* Corrigir a posição dos vetores para ficar na forma a . b = a^T.b */
      if (B.ncol() == 1){
	At = A.transpose();
	Bt = B;
      }

      else if(A.nlin() == 1){
	Bt = B.transpose();
	At = A;
      }
    }

    else if((A.nlin() == B.ncol()) && (A.ncol() == 1)){ /* Quando estão todos ao contrário. A 2º condição serve para distinguir da seguinte */
      At = A.transpose();
      Bt = B.transpose();
    }

    else if(A.ncol() == B.nlin()){ /** Tudo ok **/
      At = A;
      Bt = B;
    }
  }

  /*cout << At;
    cout << Bt;*/
  
  /* Efetuar o cálculo */
  if ((At.nlin() == 1) && (Bt.ncol() == 1) && (At.ncol() == Bt.nlin())){
    for (int i = 1; i <= At.ncol(); i++){
      val += At(1, i) * Bt(i, 1);
    }
  }

  else{
    cout << "As dimensões dos vetores em questão são incompatíveis." << endl;
    val = nan("");
  }

  return val;
}

Matrix cross(const Matrix& A, const Matrix& B)
{
  Matrix Ext(1, 3); // O resultado será sempe um vetor coluna em R³
  if (((A.nlin() > 1) && (A.ncol() > 1)) || (((B.nlin() > 1) && (B.ncol() > 1)))){
    cout << "Os objetos apresentados não são vetores. O produto externo não está definido." << endl;
    exit(EXIT_FAILURE);
  }

  else if (((A.nlin() + A.ncol()) != 4 && (A.nlin() != 3)) || ((B.nlin() + B.ncol()) != 4 && (B.nlin() != 3))){
    cout << "Os vetores têm de estar em R³ para se efetuar o produto externo." << endl;
    cout << "Apenas vetores coluna poderão ser usados para calcular um produto externo." << endl;
    /* Limitei esta função a vetores coluna por comodismo... */
    exit(EXIT_FAILURE);
  }

  else{
    Ext.set(1,1, A(2,1) * B(3,1) - A(3,1)*B(2,1));
    Ext.set(2,1, A(3,1) * B(1,1) - A(1,1)*B(3,1));
    Ext.set(3,1, A(1,1) * B(2,1) - A(2,1)*B(1,1));
  }

  return Ext;
}

/* Regime de Validade do Método Seguinte: Matrizes Hermíticas */
/* The finite-dimensional spectral theorem says that any Hermitian matrix can be diagonalized by a unitary matrix, and that the resulting diagonal matrix has only real entries. This implies that all eigenvalues of a Hermitian matrix A with dimension n are real, and that A has n linearly independent eigenvectors. Moreover, Hermitian matrix has orthogonal eigenvectors for distinct eigenvalues. Even if there are degenerate eigenvalues, it is always possible to find an orthogonal basis of Cn consisting of n eigenvectors of A. */


Matrix eigenspace(Matrix& M, Matrix& eigenvalues, const Matrix& guess, int stop)
{
  /* Inicializar a matriz dos vetores próprios */
  Matrix eigenvectors(M.ncol(), M.nlin());
  eigenvectors = 0;

  double eigen = 0;
  double eps = 1e-13;
  double dif = 10;

  // Vetores Coluna para os cálculos intermédios
  Matrix V1(1, M.nlin());
  Matrix V2(1, M.nlin());
  Matrix aux1(1, 1);
  Matrix aux2(1, 1);/* Matrizes auxiliares para cálculo dos valores próprios */
  Matrix currentVec(1, M.nlin());

  /* obter o espaço próprio gerado pela matriz M, calculando os vetores próprios um de cada vez do maior ao mais pequeno:
  -> Escreve os valores próprios associados a cada vetor próprio determinado no vetor coluna eigenvalues;
  -> Utilizar o vetor guess como aproximação inicial antes de calcular cada vetor próprio
  -> Retorna uma matriz com os vetores próprios determinados */
  
  if (M.isSymmetric() && ((eigenvalues.ncol() == 1))){

    for (int i = 1; i <= stop; i++){
      dif = 10;
      V1 = guess;
      
      /* Foge ao cálculo do maior vetor próprio */
      if (i != 1){
	for (int j = 1; j < i; j++){
	  V1 = V1 - (dot(V1, eigenvectors.vec_out(j)) * eigenvectors.vec_out(j)); //garantir que é ortogonal aos anteriores
	}
	V1 = V1.normalize();
      }
      
      /* Ciclo de iteração do método de ponto fixo para calcular cada um dos vetores próprios.
       De cada vez que é corrido, tem em atenção que o vetor próprio que é necessário obter
       seja calculado numa direção ortogonal à dos vetores já obtidos */
      
      while(abs(dif) >= eps){
	V2 = M * V1;	  

	V2 = V2.normalize();
	
	/*
	aux1 =  M * V2;
	aux2 = V2.transpose() * aux1;
	eigen = aux2(1,1);
	*/
	
	/* Foge ao cálculo do maior vetor próprio */
	if (i != 1){
	  for (int j = 1; j < i; j++){
	    V2 = V2 - (dot(V2, eigenvectors.vec_out(j)) * eigenvectors.vec_out(j)); //garantir que é ortogonal aos anteriores
	  }
	}
	/*******************************************/
	
	dif = abs(V2(M.nlin(), 1)) - abs(V1(M.nlin(), 1));
	
	/*há aqui alguma aldrabice, porque a matriz, sendo simétrica, está constantemente 
	  a gerar um vetor que é simétrico àquele que multiplicamos à esquerda na matriz
	  M. Esta "resolução" serve apenas para lidar com esta simetria */
	
	// cout << dif << endl; DEBUGGING
	
	V1 = V2;
      }
      //eigenvalues.set(i, 1, eigen);
      for(int k = 1; k <= eigenvectors.nlin(); k++){
	eigenvectors.set(k, i, V2(k, 1));
      }
    }

    for (int i = 1; i <= stop; i++){
      currentVec = eigenvectors.vec_out(i);
      aux1 =  M * currentVec;
      aux2 = currentVec.transpose() * aux1;
      eigenvalues.set(i, 1, aux2(1,1));
    }
  }
  
  else if((eigenvalues.nlin() != stop) && (eigenvalues.ncol() != 1)){
    cout << "Forneça um vetor coluna para guardar os valores próprios cujo nº de linhas coincida com a dimensão da matriz." <<endl;
    exit(EXIT_FAILURE);
  }
  else{
    cout << "A matrix não é hermitiana. Não é possível determinar os seus vetores próprios desta forma." << endl;
    exit(EXIT_FAILURE);
  }

  return eigenvectors;
}

void secularEq(Matrix& M)
{
  ofstream out_secular("secular.dat");
  
  Matrix A(M);
  Matrix Id(M.ncol(), M.nlin());
  double det;
  double eps = 1e-9;
  double h = 0.1;
  double a = -20;
  double b = 20;
  double x;

  x = a;
  Id = 0;
  for (int i = 1; i <= Id.nlin(); i++){
    Id.set(i, i, 1);
  }

  while (x < b){
    det = (A - x * Id).findDet();
    x += h;
    out_secular << x << " " << det << endl;
  }
  
}



/* Outras funções */

/* Rotina de verificação de ficheiros */
bool checkDir(const string& toRead)
{
  DIR *curdir;
  struct dirent *content;
  int c = 0;

  if ((curdir = opendir(".")) != NULL){
      while ((content = readdir(curdir)) != NULL){
	  if (toRead.compare(content->d_name) == 0){
	      cout << "Ficheiro de configuração encontrado." << endl;
	      c = 1;
	    }
	  else{
	      continue;
	    }
	}
      closedir(curdir);
    }
  
  if (c == 1) {
    return true;
  }
  else {
    return false;
  }
  
}

double quantumOsc(double k, double x)
{
  return 0.5 * k * (x*x);
}

Matrix solveSchrodinger(double (&V_x)(double, double), Matrix& Energy, Matrix& X, int npos, double lim, int stop, istream& parametros)
{
  /* Resolver H*phi = E*phi */
  
  Matrix H(npos, npos);
  Matrix M(npos, npos);

  /* Guardar os valores próprios de M = H⁻¹ */
  Matrix invEnergy(Energy);

  /* Rede 1D */
  Matrix guess(1, npos);

  /* Função de onda solução */
  Matrix phi(npos, npos);
  
  /* Parâmetros físicos */
  double h_bar;
  double m;
  double k;

  parametros >> h_bar >> m >> k;

  /* Parâmetros computacionais */
  double step = 2. * lim / (npos - 1); // step de rede
  
  /* Definir a rede unidimensional */
  for (int i = 1; i <= X.nlin(); i++){
    X.set(i, 1, (-1) * lim + (i - 1) * step);
  }

  double par = (h_bar * h_bar) / (2. * m * step * step); 

  /* Definir o vetor guess inicial */
  for (int i = 1; i <= guess.nlin(); i++){
    guess.set(i, 1, floor(((double) rand() / (double) RAND_MAX) * 10));
  }

  /* Definir a matriz hamiltoniana */
  H = 0;

  for (int i = 1; i <= H.nlin(); i++){
    for (int j = (i - 1); j < (i + 2); j++){
      if ((i == 1) && (j == 0)){
	j++;
      }

      if ((i == H.nlin()) && (j == H.ncol() + 1)){
	break;
      }
	
      if (i == j){
	H.set(i, i, 2 * par + V_x(k, X(i, 1)));
      }
      else{
	H.set(i, j, (-1) * par);
      }
    }
  }
  
  /*********** Resolver de facto a eq. ***********/

  M = H.inverse();                                 // Usar a matriz inversa para o cálculo
  phi = eigenspace(M, invEnergy, guess, stop);     // Determinar os vetores função onda, phi
  /* Update: agora é possível o utilizador especificar quantas soluções quer calcular */
  for (int i = 1; i <= invEnergy.nlin(); i++){
    Energy.set(i, 1, 1./(invEnergy(i, 1)));
    }
  
  return phi;
}



/* Solução para o problema dos <const>Objects
    ../main.cpp:35: error: passing 'const StudentT' as 'this' argument of 'int StudentT::getId()' discards qualifiers

    ../main.cpp:35: error: passing 'const StudentT' as 'this' argument of 'std::string StudentT::getName()' discards qualifiers


The objects in the std::set are stored as const StudentT. So when you try to call getId() with the const object the compiler detects a problem, namely you're calling a non-const member function on const object which is not allowed because non-const member functions make NO PROMISE not to modify the object; so the compiler is going to make a safe assumption that getId() might attempt to modify the object but at the same time, it also notices that the object is const; so any attempt to modify the const object should be an error. Hence compiler generates error message.

The solution is simple: make the functions const as:

int getId() const {
    return id;
}
string getName() const {
    return name;
}

*/
