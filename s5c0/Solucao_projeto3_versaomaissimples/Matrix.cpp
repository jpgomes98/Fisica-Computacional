//---------- VecAnyD.cpp ----------
#include <iostream>
#include "Matrix.h"
#include <stdlib.h> 


Matrix::Matrix(unsigned _nx, unsigned _ny) : nx(_nx), ny(_ny) { 
  ptr = new double*[ny];
  for(int j = 0; j < ny; j++) 
    ptr[j] = new double[nx];
} 

Matrix::Matrix(const Matrix& vec) : nx(vec.nx), ny(vec.ny) {
  ptr = new double*[ny];
  for(int j = 0; j < ny; j++) 
    ptr[j] = new double[nx];

  for(unsigned j = 0; j < ny; j++) 
  for(unsigned i = 0; i < nx; i++) 
    ptr[j][i] = vec.ptr[j][i];
}

Matrix::~Matrix() { 
  for(int j = 0; j < ny; j++) delete[] ptr[j];
  delete[] ptr;
}

unsigned Matrix::Nx() const { return nx; } 
unsigned Matrix::Ny() const { return ny; } 


   /*   
std::ostream& operator<<( std::ostream& out, const Matrix & r ) { 
  for( unsigned i = 0; i < r.size(); ++i ) out  << r.get(i) << "\t";
  std::cout << std::endl;
  return out;
}*/


Matrix& Matrix::operator=( const Matrix & r2 ){
  for(unsigned j = 0; j < ny; j++) 
  for(unsigned i = 0; i < nx; i++) 
    ptr[j][i] = r2.ptr[j][i];
  return *this;
}

Matrix& Matrix::operator=( const double a ){
  for(unsigned j = 0; j < ny; j++) 
  for(unsigned i = 0; i < nx; i++) 
    ptr[j][i] = a;
  return *this;
}


Matrix Matrix::operator+(const Matrix & r2 ) const { // operador para a soma
  Matrix ret(Nx(), Ny());
  for(unsigned j = 0; j < ny; j++) 
  for(unsigned i = 0; i < nx; i++) 
    ret.ptr[j][i] = ptr[j][i] + r2.ptr[j][i];
  return ret;
}

Matrix operator*(const double a, const Matrix & r2 ) { 
  Matrix ret(r2.Nx(), r2.Ny());
  for(unsigned j = 0; j < r2.Ny(); j++) 
  for(unsigned i = 0; i < r2.Nx(); i++) 
    ret.ptr[j][i] = r2.ptr[j][i] * a;
  return ret;
}

Matrix Matrix::operator/(const double a) const { 
  Matrix ret(Nx(), Ny());
  for(unsigned j = 0; j < ny; j++) 
  for(unsigned i = 0; i < nx; i++) 
    ret.ptr[j][i] = ptr[j][i] / a;
  return ret;
}


double Matrix::operator()(unsigned i, unsigned j) const { return ptr[i][j]; }

double& Matrix::operator()(unsigned i, unsigned j) { return ptr[i][j]; }



Matrix med(const Matrix& r2){
  Matrix r1(r2.Nx(), r2.Ny());
  for(unsigned j = 0; j < r2.Ny(); j++) 
  for(unsigned i = 0; i < r2.Nx(); i++) {
    if( i==0 || i == r2.Nx()-1 || j==0 || j==r2.Ny()-1) r1.ptr[j][i] = r2.ptr[j][i];
    else r1.ptr[j][i] = .25* (r2.ptr[j][i+1] + r2.ptr[j][i-1] + r2.ptr[j+1][i] + r2.ptr[j-1][i]); 
  }
  return r1;
}


Matrix vecDx2(const Matrix& r2){
  Matrix r1(r2.Nx(), r2.Ny());
  for(unsigned j = 0; j < r2.Ny(); j++) 
  for(unsigned i = 0; i < r2.Nx(); i++) {
    if( i==0 || i == r2.Nx()-1 || j==0 || j==r2.Ny()-1) r1.ptr[j][i] = 0.;
    else r1.ptr[j][i] = r2.ptr[j][i+1] -2. * r2.ptr[j][i] + r2.ptr[j][i-1]; 
  }
  return r1;
}

Matrix vecDy2(const Matrix& r2){
  Matrix r1(r2.Nx(), r2.Ny());
  for(unsigned j = 0; j < r2.Ny(); j++) 
  for(unsigned i = 0; i < r2.Nx(); i++) {
    if( i==0 || i == r2.Nx()-1 || j==0 || j==r2.Ny()-1) r1.ptr[j][i] = 0.;
    else r1.ptr[j][i] = r2.ptr[j+1][i] -2. * r2.ptr[j][i] + r2.ptr[j-1][i]; 
  }
  return r1;
}

double SumAbsDif(const Matrix& r1, const Matrix& r2){
  double dif = 0.;
  for(unsigned j = 0; j < r2.Ny(); j++) 
  for(unsigned i = 0; i < r2.Nx(); i++) 
    dif += abs(r1.ptr[j][i] - r2.ptr[j][i]);
  return dif;
}





