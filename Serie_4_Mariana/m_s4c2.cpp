#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

double relax(double w, double x, double f)
{
  double x_f = 0;
  x_f=w*f+(1-w)*x;
  
  return x_f;
}

int main()
{
  double w, x, f, x0, x1, w0, wf;
  int d=0;

  ofstream Data ("Data.dat");
  
  cout << "BEM-VINDO!" << endl;
  cout << "Insira os valores de w iniciais." << endl;
  cin >> w0;
  cout << "Insira os valores de w finais." << endl;
  cin >> wf;
  
  cout << "Insira os valores de x inicial." << endl;
  cin >> x0;

  x = x0;
  w=w0;

  while(w<wf)
    { 
      while(1)
	{
	  f = cos(x)*cos(x);
	  x1 = relax(w, x, f);

	  if(abs(x1-x)<pow(10,-6))
	    {
	      break;
	    }

	  x=x1;
	  ++d;
	}

      Data << w <<" "<< d <<endl;
      w= w + 0.01;
      x = x0;
      d=0;
    }


  
  Data.close();
  return 0;
}
