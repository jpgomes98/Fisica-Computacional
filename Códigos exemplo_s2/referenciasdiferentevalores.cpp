// referencia.cpp

// uma referenia e como um ponteiro, mas tem de ser inicializada
// e depois nao pode ser re-apontada outra vez

#include <iostream>

void fvalue( float x ) // funcao com valor
    {
	std::cout << " o endereco em fvalue e" << &x << "\n";
	}

void fref( float& x ) // funcao com referencia
    {
	std::cout << " o endereco em fref e" << &x << "\n";
	}


void set_zero( float& x ) //com referencia que anula o x
    {
	x = 0;
	}


// agora com o mesmo nome! mas funciona
void set_zero( float* p ) // com ponteiro que anula * P
	{
    if ( p )
		*p = 0;
	}

void print_float( const float& f )  // esta nao pode alterar o f
    {
	std::cout << f << '\n';
	}

int main(){
float x = 3.0;
std::cout << " o endereco de x e" << &x << "\n";
fvalue( x ); // aqui e diferente pois passou para a funcao uma copia de x (o valor)
fref( x ); // aqui e igual pois passou para a funcao o proprio x
float y = x;
fvalue( y ); // aqui passa o mesmo valor que tinha x
fref( y );  // aqui a referencia e diferente pois refere-se a variavel y
float& r = x; // agora r e uma referencia e e igual nao ao valor mas a referencia de x
fvalue( r ); // mais uma vez e o mesmo valor que tinha x
fref( r ); // aqui ja temos a referencia de x de novo
std::cout << "Valor de x: " << x << '\n';
set_zero( x );
std::cout << "Novo valor de x: " << x << '\n';
//Nao funciona:
//set_zero( 3 + x ); 
//Mas isto ja funciona
print_float( 3 + x ); // 3 + x e convertido em referencia para constante, mas nao em referencia



     
      
    return  0;

}
 
