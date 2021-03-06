#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <stdio.h>

using namespace std;

class Poison_2d {
public:
  Poison_2d(void);
  double mat[100][100];
  int n_pos;
  double h1;
  double p;
  void poison(int, int);

  friend double normaV (double *mat, int n_pos);
};

Poison_2d::Poison_2d()  
{
  n_pos = 100;
  h1 = 0;
  p = 0;
}

void Poison_2d::poison (int i, int j)
{
  if (i==20 && j==45 || i==53 && j==23)
    {
      p=2;
    }
  else
    {
      p=0;
    }

  mat[i][j] = (mat[i-1][j]+mat[i+1][j]+mat[i][j+1]+mat[i][j-1] + h1*h1*p)/4.;
}


double normaV (double *mat, int &n_pos) // norma vetorial
{
  double s = 0;
  for (int i = 0; i < n_pos; i++)
    {
      s += mat[i] * mat[i];
    }

  return sqrt(s);
}


int main ()
{
  Poison_2d P2d;
  int d, a, b;
  double a1, a2, b1, b2, x, y;
  double v_1, v_2, v_3, v_4;
  double h[2];

  ofstream two_d("Two_Dimension.dat");
  
  cout << "Bem vindo!"<< endl;
  cout << "Insira valores para condições fronteira"<< endl;
  cout << "Valores para as coordenadas dos vértices do quadrilátero (a1, a2, b1, b2)"<< endl;
  cin >> a1;
  cin >> a2;
  cin >> b1;
  cin >> b2;

  cout << "Valores do potencial na fronteira (v_1, v_2, v_3, v_4)"<<endl;
  cin >> v_1;
  cin >> v_2;
  cin >> v_3;
  cin >> v_4;
  
  h[0]= (a2-a1)/((double) P2d.n_pos);
  h[1]= (b2-b1)/((double) P2d.n_pos);

  P2d.h1 = sqrt(h[0]*h[0]+h[1]*h[1]);
  
  for(int v=0; v<P2d.n_pos; v++ )
    {
      P2d.mat[v][0]=v_1;
      P2d.mat[v][P2d.n_pos-1]=v_2;
      P2d.mat[0][v]=v_3;
      P2d.mat[P2d.n_pos-1][v]=v_4;
    }
    
  while(normaV<0.001)
    {
      for(int i1=1; i1<P2d.n_pos-1; i1++)
      {
	for(int j1=1; j1<P2d.n_pos-1; j1++)
	  {
	    P2d.poison(i1, j1);
	  }
      }
      
      ++d;
    }

  for(int i_1=0; i_1<P2d.n_pos; i_1++)
    {
      for(int j_1=0; j_1<P2d.n_pos; j_1++)
	{
	  x = i_1 * h[0];
	  y = j_1 * h[1];
	  two_d << x << " "<< y << " "<<P2d.mat[i_1][j_1]<< endl;
	}
    }
  
  two_d.close();
  return 0;
  
  
}
