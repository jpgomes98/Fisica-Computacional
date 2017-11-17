#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <stdio.h>

using namespace std;

double poison (double v_n1, double v_n_1, double p, double h)
{
  double v_n;

  v_n = (v_n_1+v_n1)/2 + h*h*p;

  return v_n;
}


int main ()
{
  double v0, v_max, p=0;
  double v_n_1, v_n1, h, d, a, b, i3=0;
  int n, i1= 1;  

  ofstream one_d("One_Dimension.dat");

  cout << "Bem vindo!"<< endl;
  cout << "Insira valores para condições fronteira"<< endl;
  cout << "v0:"<< endl;
  cin >> v0;
  cout << "a:"<<endl;
  cin >> a;    
  cout << "v_max:"<< endl;
  cin >> v_max;
  cout << "b:"<<endl;
  cin >> b;
  cout << "Dimensão do vetor (n)"<< endl;
  cin >> n;


  double vec[n];

  for(int i=0; i<n; i++)
    {
      vec[i]=0;
    } 
  
  h= (b-a)/((double) n);

  vec[0]=v0;
  vec[n-1]=v_max;


  while(d<10000)
    {
      for(i1=1; i1<n-1; i1++)
      {
	vec[i1]=poison(vec[i1+1], vec[i1-1], p, h);
      }
      
      ++d;
    }

  for(int i2=0; i2<n; i2++)
    {
      i3= i2 * h;
      one_d << i3 << " " << vec[i2]<< endl;
    }
  
  one_d.close();
  return 0;
  
  
}
