#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <stdio.h>
#include "s4c4_class_header.h"

using namespace std;

namespace Aux {
extern int n_pos;
extern double h;
extern double p;
}

using namespace Aux;

class poison_2d {
public:
  double mat[100][100];
  void poison(int, int);
  
  poison_2d(int a, int b)
  {
    for (a; a<100; a++)
      {
	for (b; b<100; b++)
	  {
	    mat[a][b]=0;
	  }
      }
  }
  
};

void poison_2d::poison (int i, int j)
{
  mat[i][j] = (mat[i-1][j]+mat[i+1][j]+mat[i][j+1]+mat[i][j-1] + h1*h1*p)/4.;
} 


int main ()
{
  poison_2d Poison_2d;
  int d, a, b;
  double a1, a2, b1, b2, x, y;
  double v_1, v_2, v_3, v_4;
  double h[2];

  ofstream two_d("Two_Dimension.dat");
  
  p=0;
  n_pos=100;
  
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
  
  h[0]= (a2-a1)/((double) n_pos);
  h[1]= (b2-b1)/((double) n_pos);

  h1 = sqrt(h[0]*h[0]+h[1]*h[1]);
  
  for(int v=0; v<n_pos; v++ )
    {
      Poison_2d.mat[v][0]=v_1;
      Poison_2d.mat[v][n_pos-1]=v_2;
      Poison_2d.mat[0][v]=v_3;
      Poison_2d.mat[n_pos-1][v]=v_4;
    }
    
  while(d<10000)
    {
      for(int i1=1; i1<n_pos-1; i1++)
      {
	for(int j1=1; j1<n_pos-1; j1++)
	  {
	    if (i1==2 && j1==2 || i1==53 && j1==23)
	      {
		Poison_2d.mat[i1][j1]=2;
	      }
	    else
		  {
		    Poison_2d.poison(i1, j1);
		  }
	  }
      }
      
      ++d;
    }

  for(int i_1=0; i_1<n_pos; i_1++)
    {
      for(int j_1=0; j_1<n_pos; j_1++)
	{
	  x = i_1 * h[0];
	  y = j_1 * h[1];
	  two_d << x << " "<< y << " "<<Poison_2d.mat[i_1][j_1]<< endl;
	}
    }
  
  two_d.close();
  return 0;
  
  
}
