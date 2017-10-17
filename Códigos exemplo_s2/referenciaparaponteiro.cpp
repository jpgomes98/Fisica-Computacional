// referencia.cpp

#include <iostream>

// funcao para incrementar 
// que usa ponteiro e referencia
void anula(int*& i){i = NULL;}

void incrementa(int*& i){i ++;}


int main(){
    int x = 2;
    int* i = &x; 
    std::cout << " i= " << i <<std::endl;
    
    anula(i);
    std::cout << " i= " << i <<std::endl;
     
     
    int* j = 0; // aqui 0 e o ponteiro nulo
    std::cout << " j= " << j <<std::endl;
    
    incrementa(j);
    incrementa(j);
    // perigoso, porque fica a apontar
    // para uma zona proibida da memoria
    std::cout << " j= " << j <<std::endl;
 
    std::cout << "Size de um int: " << sizeof(int) << std::endl;
      
    return  0;
    }
     
      
