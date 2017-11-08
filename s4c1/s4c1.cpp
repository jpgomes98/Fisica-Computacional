#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

struct A{
  int w;
  int h;
  int area(){
    return w*h;
  }
};

class Triangulo {
  int base;
  int altura;
public:
  Triangulo (); /* Overload de constructors */
  Triangulo (int, int); /* Constructor */
  void definir (int, int); /* Rotina equivalente */
  double area (void) {
    return (double) (0.5 * base * altura);
      };
};

Triangulo::Triangulo()
{
  base = 2;
  altura = 4;
}
Triangulo::Triangulo(int x, int y)
{
  base = x;
  altura = y;
}

void Triangulo::definir (int x, int y)
{
  base = x;
  altura = y;
}


int main ()
{
  A myStruct;
  A *p;
  
  Triangulo myTri1, myTri2(5,6);
  Triangulo *foo, *bar, *other;

  /* Definir os valores apontados pelas variáveis anteriores */

  p = &myStruct;
  foo = &myTri1;
  bar = new Triangulo;
  other = new Triangulo[2];

  other[1].definir(2,5);
  
  cout << "A área do T1 estático é: " << myTri1.area() << endl;
  cout << "A área do T2 estático é: " << myTri2.area() << endl;
  cout << "A área do T3 dinâmico é: " << (*foo).area() << endl;
  cout << "A área do T4 dinâmico é: " << bar->area() << endl;
  cout << "A área do T5 dinâmico é: " << other[0].area() << endl;
  cout << "A área do T6 dinâmico é: " << other[1].area() << endl;
  

  /*
  myStruct.w = 10;
  myStruct.h = 5;
  cout << myStruct.area() << endl;
  */

  delete bar;
  delete[] other;
  
  return 0;
  
}
