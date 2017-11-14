#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

class Vector{
  size_t length;
  double *v;

public:
  Vector(const Vector& v); // construtor que recebe um vetor na main e atualiza o vetor privado para ter o tamanho do recebido
  explicit Vector(size_t len); //construtor que recebe um tamanho para o vetor prvado
  ~Vector(); // destrutor, não precisa de ser chamado para eliminar os objetos da classe
  size_t size() const;
  double get(size_t i) const;
  void set(size_t i, double x);
};

/* Construtores */

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

/* Função que imprime a componente i do vetor */

double Vector::get(size_t i) const
{
  return v[i];
}

void Vector::set(size_t i, double x)
{
  v[i] = x;
}


int main()
{
  Vector u(4);
  Vector vetor(5);

  for (int i = 0; i < u.size(); i++)
    {
      u.set(i, i);
    }

  for (int j = 0; j < vetor.size(); j++)
    {
      vetor.set(j, j);
    }
  
  Vector x(vetor);

  cout << "O vetor u tem um tamanho de: " << u.size() << endl;
  cout << "O vetor x tem um tamanho de: " << x.size() << endl;

  cout << "Componentes de u: ";
  for (int i = 0; i < u.size(); i++)
    {
      cout << u.get(i) << " ";
    }

  cout << "\n";

  cout << "Componentes de x: ";
  for (int i = 0; i < x.size(); i++)
    {
      cout << x.get(i) << " ";
    }

  cout << "\n";
  
  return 0;
}
