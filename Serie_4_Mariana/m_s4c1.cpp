#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

double relax(double w, double x, double f)
{ 
  x=w*f+(1-w)*x;
  
  return x;
}

int main()
{
  double w, x, f, x0, x1;

  ofstream Data ("Data.dat");
  
  cout << "BEM-VINDO!" << endl;
  cout << "Insira os valores de w." << endl;
  cin >> w;
  cout << "Insira os valores de x inicial." << endl;
  cin >> x0;

  x = x0;
  
  while(1)
    {
      f = cos(x)*cos(x);
      x1 = relax(w, x, f);
      Data << x <<" "<< f <<endl;

      if(abs(x1-x)<pow(10,-6))
	{
	  cout << x << " " << f <<endl;
	  break;
	}

      x=x1;
    }

  Data.close();
  return 0;
}
