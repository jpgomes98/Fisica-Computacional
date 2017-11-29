#ifndef VECANYD_H
#define VECANYD_H

//---------- VecAnyD.h ----------
#include <iostream>

class Matrix {
  private:
  unsigned nx, ny;
  double **ptr;
  public:
  //construtor standard 
  explicit Matrix(unsigned _nx, unsigned _ny); // explicit proíbe usar = na construção
  Matrix(const Matrix& vec); //construtor por cópia
  ~Matrix(); //Destrutor
  unsigned Nx() const;
  unsigned Ny() const;


  Matrix& operator=( const Matrix & r2 ); 
  Matrix& operator=( const double a ); 

  Matrix operator+( const Matrix & r2 ) const;
  Matrix operator+( const double a ) const;
  friend Matrix operator+( const double a, const Matrix & r2 );
  friend Matrix operator*( const double a, const Matrix & r2 );
  Matrix operator/(const double a) const;

  Matrix operator-( const Matrix & r2 ) const;
  Matrix operator-( ) const;

  double operator()(unsigned i, unsigned j) const;
  double& operator()(unsigned i, unsigned j);

  friend Matrix med(const Matrix& r2);
  friend Matrix vecDx2(const Matrix& r2);
  friend Matrix vecDy2(const Matrix& r2);
  friend double SumAbsDif(const Matrix& r1, const Matrix& r2);
  

  //friend Matrix operator+( const Matrix & r1, const Matrix & r2 );
  friend std::ostream& operator<<( std::ostream& out, const Matrix & r ); // operador para a escrita
		

  friend double dot( const Matrix & r1, const Matrix & r2 ); // função para o produto interno

};

#endif
