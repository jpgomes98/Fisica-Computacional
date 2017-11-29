#include <iostream>
#include <fstream>  
#include <stdlib.h> 
#include <math.h>
#include <ctime>
#include "Matrix.h" 

using namespace std;



int main(){
  
  Matrix A(3, 3);
  A = 3;

  srand(time(NULL));

  for (int i = 1; i <= A.Ny(); i++)
    {
      for (int j = 1; j <= A.Nx(); j++)
	{
	  A.set(i, j, ((double) rand() / (double) (RAND_MAX)));
	}
    }
  cout << A << endl;
  
  A.set(4,4,5);
  cout << A << endl;

  return 0; 
} 
