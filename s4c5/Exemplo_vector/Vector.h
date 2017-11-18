#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

class Vector{
  
  size_t length;
  double *v;
  
public:
  
  Vector(const Vector& v);// construtor que recebe um vetor na main e atualiza o vetor privado para ter o tamanho do recebido
  explicit Vector(size_t len); //construtor que recebe um tamanho para o vetor privado
  ~Vector(); // destrutor, não precisa de ser chamado para eliminar os objetos da classe
  size_t size() const;
  double get(size_t i) const;
  void set(size_t i, double x);
  Vector&  operator=(const Vector& a);
};

ostream& operator<<(ostream& out, const Vector& u);

#endif
