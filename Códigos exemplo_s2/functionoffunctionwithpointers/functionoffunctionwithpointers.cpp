// functionoffunctionwithpointers.cpp -  Script 6.1

#include <cstdlib>
#include <iostream>
#include "fheader.h"

using namespace std;

int main(){
    
    
    // defines the type of variables
    
    float xmin , xmax ;
    int npoints;

    cout<< " you will be prompted to enter 2 floats for xmin and xmax \n"; 
    cin>> xmin >> xmax;
    
    cout<< " you will be prompted to enter 1 int for the number of integration points \n"; 
    cin>> npoints;

    float result=0;

    result=integralrect(&function,xmin,xmax,npoints);
    // o & , e comercial,  pode se usar quando se quer retirar o endereco da funcao
    // se bem que aqui nao e necessario
       
    cout<< " the output a the numerical integration is, \n" << result; 



   return 0;
}
