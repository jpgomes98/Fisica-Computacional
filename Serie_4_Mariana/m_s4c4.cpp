#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <stdio.h>

using namespace std;

double poison_2D (double v_i1_j, double v_i_1_j, double v_i_j_1, double v_i_j1, double p, double h)
{
  double v_n;

  v_n = (v_i1_j+v_i_1_j+v_i_j1+v_i_j_1)/4 + h*h*p/(4);
  

  return v_n;
}


int main ()
{
  int n_pos=100, n_max=1000, d;
  double a1, a2, b1, b2, p=0,x, y;
  double v_i1_j, v_i_1_j, v_i_j1, v_i_j_1, v_i_j;
  double v_1, v_2, v_3, v_4, h1;
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

  double mat[n_pos][n_pos];

  for(int i=0; i<n_pos; i++)
    {
      for(int j=0; j<n_pos; j++)
	{
	  mat[i][j]=0;
	}
    } 
  
  h[0]= (a2-a1)/((double) n_pos);
  h[1]= (b2-b1)/((double) n_pos);

  h1= sqrt(h[0]*h[0]+h[1]*h[1]);
  
  for(int v=0; v<n_pos; v++ )
    {
      mat[v][0]=v_1;
      mat[v][n_pos-1]=v_2;
      mat[0][v]=v_3;
      mat[n_pos-1][v]=v_4;
    }
    
  while(d<10000)
    {
      for(int i1=1; i1<n_pos-1; i1++)
      {
	for(int j1=1; j1<n_pos-1; j1++)
	  {
	    if (i1==2 && j1==2 || i1==53 && j1==23)
	      {
		mat[i1][j1]=2;
	      }
	    else
		  {
		    mat[i1][j1]=poison_2D(mat[i1-1][j1], mat[i1+1][j1], mat[i1][j1-1], mat[i1][j1+1], p, h1);
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
	  two_d << x << " "<< y << " "<<mat[i_1][j_1]<< endl;
	}
    }
  
  two_d.close();
  return 0;
  
  
}
