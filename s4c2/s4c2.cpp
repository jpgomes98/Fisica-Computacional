#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

/* Eq. Disponíveis */

/* 1) f(x) = cos(x)^2 */

double f1 (double x)
{
  return cos(x) * cos(x);
}

/* Tentativa de implementar classes com métodos iterativos */

class Pfixo {
public:
  Pfixo();
  double x1;
  double x2;
  double (*f)(double);
  double w;
  void iter_relax(void);
};

/* Construtor */

Pfixo::Pfixo()
{
  x1 = 0;
  x2 = 0;
  w = 0.3;
  f = &f1;
}

void Pfixo::iter_relax()
{
  x2 = w * f(x1) + (1 - w) * x1;
}

int main ()
{
  Pfixo eq1;
  double stop = 1e-6;
  int it = 0;

  
  cout << "Introduza o valor inicial: " << endl;
  cin >> eq1.x1;
  
  while(abs(eq1.x2 - eq1.x1) >= stop)
    {
      eq1.x1 = eq1.x2;
      eq1.iter_relax();
      it++;
      cout << abs(eq1.x2 - eq1.x1) << endl;
    }

  cout << "A solução encontrada para a equação é: " << eq1.x2 << endl;
  cout << "Foram precisas " << it << " iteradas para obter este valor." << endl;

  return 0;
}
