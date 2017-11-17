#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <stdio.h>

using namespace std;

class Poison_3d {
public:
  Poison_3d(void);
  double mat[100][100][100];
  int n_pos;
  double h1;
  double p;
  void poison(int, int, int);
};

Poison_3d::Poison_3d()  
{
  n_pos = 100;
  h1 = 0;
  p = 0;
}

void Poison_3d::poison (int i, int j, int k)
{
  if (i==20 && j==45 && k==34 || i==53 && j==23 && k==17)
    {
      p=2;
    }
  else
    {
      p=0;
    }

  mat[i][j][k] = (mat[i-1][j][k]+mat[i+1][j][k]+mat[i][j+1][k]+mat[i][j-1][k]+ mat[i][j][k-1]+mat[i][j][k+1])/6. + (h1*h1*p)/4.;
} 


int main ()
{
  Poison_3d P3d;
  int d;
  double a1, a2, b1, b2, c1, c2, x, y, z;
  double v_1, v_2, v_3, v_4, v_5, v_6;
  double h[3];

  ofstream three_d("Three_Dimension.dat");
  
  cout << "Bem vindo!"<< endl;
  cout << "Insira valores para condições fronteira"<< endl;
  cout << "Valores para as coordenadas dos vértices do quadrilátero (a1, a2, b1, b2, c1, c2)"<< endl;
  cin >> a1;
  cin >> a2;
  cin >> b1;
  cin >> b2;
  cin >> c1;
  cin >> c2;
  

  cout << "Valores do potencial na fronteira (v_1, v_2, v_3, v_4, v_5, v_6)"<<endl;
  cin >> v_1;
  cin >> v_2;
  cin >> v_3; 
  cin >> v_4;
  cin >> v_5; 
  cin >> v_6;

  cout << "Muito obrigada!" <<endl;
  
  h[0]= (a2-a1)/((double) P3d.n_pos);
  h[1]= (b2-b1)/((double) P3d.n_pos);
  h[2]= (c2-c1)/((double) P3d.n_pos);
  
  P3d.h1 = sqrt(h[0]*h[0]+h[1]*h[1]+h[2]*h[2]);
  
  for(int i=0; i<P3d.n_pos; ++i)
    {
      for(int j=0; j<P3d.n_pos; ++j)
	{
	  for(int k=0; k<P3d.n_pos; ++k)
	    {
	      if(i==0)
		{
		   P3d.mat[i][j][k]=v_1;
		}

	      if(i==P3d.n_pos-1)
		{
		  P3d.mat[i][j][k]=v_2;
		}
	      if(j==0)
		{
		   P3d.mat[i][j][k]=v_3;
		}

	      if(j==P3d.n_pos-1)
		{
		  P3d.mat[i][j][k]=v_4;
		}

	      if(k==0)
		{
		   P3d.mat[i][j][k]=v_5;
		}

	      if(k==P3d.n_pos-1)
		{
		  P3d.mat[i][j][k]=v_6;
		}
	     
	    }
	}
    }
  while(d<20000)
    {
      for(int i1=1; i1<P3d.n_pos-1; i1++)
	{
	  for(int j1=1; j1<P3d.n_pos-1; j1++)
	    {
	      for(int k1=1; k1<P3d.n_pos-1; k1++)
		P3d.poison(i1, j1, k1);
	    }
	}
      
      ++d;
    }

  for(int i_1=0; i_1<P3d.n_pos; i_1++)
    {
      for(int j_1=0; j_1<P3d.n_pos; j_1++)
	{
	  x = i_1 * h[0];
	  y = j_1 * h[1];
	    
	  cout << P3d.mat[i_1][j_1][50]<<endl;
	  three_d << x << " " << y << " " <<P3d.mat[i_1][j_1][50]<< endl;
	}
	
    }
  
  three_d.close();
  return 0;
  
  
}
