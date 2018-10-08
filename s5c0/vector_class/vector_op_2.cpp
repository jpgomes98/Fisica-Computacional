
// overloadefriends.cpp
#include <iostream>

using namespace std;

// um overload corresponde a definir os operadores (+, *, etc que ja existem)
// para novos tipos
 
class Vec3d{ // para vectores num espaco a 3 dimensoes
public: // para usar fora da classe    
  float r[3];
  Vec3d() {} // construtor    
  Vec3d( float x, float y, float z ) // os 3 elementos do vector
  {
    r[0] = x;
    r[1] = y;
    r[2] = z;
  }                     
  float x() const { return r[0];};
  float& x()   { return r[0]; }; // retorna o x quando se pode alterar o objecto 
  float y() const{ return r[1]; };  // retorna o y
  float& y() {return r[1]; }; 
  float z() const  {   return r[2]; }; // retorna o z
  float& z() { return r[2]; };
  
  friend Vec3d operator! (const Vec3d& r1);
  friend Vec3d operator* (const Vec3d& v1, const Vec3d& v2);
};

Vec3d operator!(const Vec3d& r1)
{
  Vec3d negado;
  for (int i = 0; i < 3; i++)
    {
      negado.r[i] = -r1.r[i];
    }
  return negado;
}

Vec3d operator*(const Vec3d& v1, const Vec3d& v2)
{
  Vec3d externo;
  externo.r[0] = v1.r[1]*v2.r[2] - v1.r[2]*v2.r[1];
  externo.r[1] = v1.r[2]*v2.r[0] - v1.r[0]*v2.r[2];
  externo.r[2] = v1.r[0]*v2.r[1] - v1.r[1]*v2.r[0];
  
  return externo;
}

Vec3d operator=(const Vec3d& r)
{
  
}

int main()
{
  Vec3d u(3,4,5), v;
  Vec3d a(1,2,3);
  Vec3d w;

  cout << "O vetor u tem como componentes " << u.r[0] << " " << u.r[1] << " " << u.r[2] << endl;
  cout << "Obtendo o vetor negado..." << endl;

  v = !u;

  cout << "As novas componentes de u são " << v.r[0] << " " << v.r[1] << " " << v.r[2] << endl;

  w = u*a;
  cout << "As componentes de w = u x v são " << w.r[0] << " " << w.r[1] << " " << w.r[2] << endl;
  return 0;
}
