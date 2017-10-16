#include <cstdlib>
#include <iostream>
#include "fheader.h"

using namespace std;

// this is a function, the integral, with a pointer to a function, for the integrand

float integralrect(float (*function)(float), float xmin, float xmax, int npoints){
      // o * e para termos um ponteiro, ou seja uma variavel-funcao dinamica 
      // ou seja desconhecida durante a compilacao
      // os () sao para dizer que temos um ponteiro para uma funcao
      // sem () teriamos uma funcao que retornaria um ponteiro para float

      float result=0; //initializes the integral

      float dx = ( xmax - xmin ) / npoints; //integration step
      
      // sums the integral numerically, here for rectangular approximation
      for( int i=0; i<npoints; ++i) result += function(xmin + (i + 1/2) * dx) * dx ;
      
      return result;
      }
