#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "Vector.h"

/* Construtores */

using namespace std;

Vector::Vector(const Vector& vec)
{
  length = vec.length;
  v = new double[length];
  for (int i = 0; i < length; i++)
    {
      v[i] = vec.v[i]; // atribuir os elementos do vetor recebido ao privado
    }
  cout << "Vetor inicializado através da atribuição de outro objeto." << endl;
}

Vector::Vector(size_t len) 
{
  length = len;
  v = new double(length);
  cout << "Vetor inicializado através do compr." << endl;
}

/* Destrutor */
Vector::~Vector(void)
{
  cout << "Vetor destruido" << endl;
}

/* Função que imprime v.length */
size_t Vector::size() const
{
  return length;
}

/* Função Que Imprime A Componente I Do Vetor */
double Vector::get(size_t i) const
{
  return v[i];
}

void Vector::set(size_t i, double x)
{
  v[i] = x;
}

Vector& Vector::operator=(const Vector& a)
{
  size_t new_size;
  if (this == &a){
    return *this;
    }
  else{
    delete[] v;
    new_size = a.size();
    v = new double[new_size];
    for (int i = 0; i < new_size; i++){
      v[i] = a.v[i];
      }

    return *this;
  }
}


ostream& operator<<(ostream& out, const Vector& u)
{
  for (int i = 0; i < u.size(); i++)
    {
      if (i == 0)
	{
	  out << "(" << u.get(i);
	}
      else
	{
	  out << ", " << u.get(i);
	}
    }

  out << ")" << endl;
  return out;
}
