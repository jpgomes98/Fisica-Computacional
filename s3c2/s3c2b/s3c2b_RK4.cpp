  
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "s3.h"

using namespace std;

int main() 
{ 
  double N0, N1, tf, lbd;
  double h = 0.5;

  cout << "Insira os valores da constante de decaimento " << endl;
  cin >> lbd;
  cout << "Introduza o valor inicial de N" << endl;
  cin >> N0;
  cout << "Introduza o tempo final" << endl;
  cin >> tf;

  N1 = N0;
  
  Euler(N1, h, tf, lbd);
  RungeKutta(N1, h, tf, lbd);
  analiticaDecaimento(N0, h, tf, lbd);

  return 0;
}
