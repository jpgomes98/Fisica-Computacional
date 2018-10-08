#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "Vector.h"

using namespace std;

int main()
{
  int y_n;
  size_t n_;
  double a = 0;
  Vector u(4);
  Vector vetor(5);

  cout << "Programa de operação de vetores. Versão 2 - 17/11/2017" << endl;
  cout << "Pretende gerar algum vetor? (0:1) " << endl;
  cin >> y_n;

  if (y_n == 1)
    {
      cout << "N dim?" << endl;
      cin >> n_;
    }
  else
    {
      cout << "Então observa..." << endl;
    }

   for (int i = 0; i < u.size(); i++)
    {
      u.set(i, i);
    }

  for (int j = 0; j < vetor.size(); j++)
    {
      vetor.set(j, j);
    }

  if (y_n == 1)
    {
      Vector w(n_);
      w = vetor;
      cout << w;
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
  cout << endl;

  cout << "Versão alternativa de apresentação das componentes:" << endl;
  cout << x;

  cout << "\n";
  
  return 0;
}
