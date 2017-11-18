// overloadefriends.cpp

#include <iostream>
using namespace std;


// um overload corresponde a definir os operadores (+, *, etc que ja existem)
// para novos tipos

 
 
class Vec3d // para vectores num espaco a 3 dimensoes
      {
      private:  // so para usar dentro da classe
              float r[3];
              
      public: // para usar fora da classe
      
             Vec3d() {} // construtor
             
             Vec3d( float x, float y, float z ) // os 3 elementos do vector
                    {
                    r[0] = x;
                    r[1] = y;
                    r[2] = z;
                    } 
                    
             float x() const // retorna o x quando nao e alterado
                   {
                   return r[0];
                   }
             float& x() // retorna o x quando se pode alterar o objecto
                   {
                    return r[0];
                    }
                    
             float y() const // retorna o y 
                   {
                   return r[1];
                   }
             float& y() {
                    return r[1];
                    } 
                    
             float z() const // retorna o z
                   {
                   return r[2];
                   }
             float& z() {
                    return r[2];
                    }
                    
             friend float dot( const Vec3d& r1, const Vec3d& r2 );
                    
             friend Vec3d operator+( const Vec3d& r1, const Vec3d& r2 ); 
             // aqui esta o overload do operador + ( binario e nao o unario)
             // não é um membro da classe por isso necessita do friend, 
             // const, afirma que nao altera o valor do argumento
             // friend tem acesso a tudo o que e privado da classe
             // & permite passar por referencia, sem copiar ou seja passando menos memoria
	     friend Vec3d operator!( const Vec3d& r1); 

             friend ostream& operator<<( ostream& out, const Vec3d& r );
		
             // destrutor não é necessário pois não foi memória alocada
             // no construror com por exemplo um ponteiro para new

};

float dot( const Vec3d& r1, const Vec3d& r2 ) {
      float res = 0;
      for( int i = 0; i < 3; ++i )
           res +=  r1.r[i] * r2.r[i];
      return res;
      }


Vec3d operator+( const Vec3d& r1, const Vec3d& r2 ) {
      Vec3d ret;
      for( int i = 0; i < 3; ++i )
           ret.r[i] = r1.r[i] + r2.r[i];
      // como o operador é amigo da classe pode aceder à parte privada de Vec3d
      return ret;
      }

Vec3d operator! ( const Vec3d& r1) {
  Vec3d negado;
      for( int i = 0; i < 3; ++i )
	negado.r[i] = -r1.r[i];
      return negado;
      }

ostream& operator<<( ostream& out, const Vec3d& r ) {
     out << "( " << r.r[0] << " , " << r.r[1] << " , " << r.r[2] << " )";
     }

int main()
{
    // aceita input
    cout<<"de 3 elementos do 1o vector \n";
    Vec3d r1; 
    cin>> r1.x()>>r1.y()>>r1.z();
    cout<<"de 3 elementos do 2o vector \n";
    Vec3d r2; 
    cin>> r2.x()>>r2.y()>>r2.z();

    //escreve no ecran
    cout<<"a soma e \n" <<r1+r2 <<"\n";  
    cout<<"o produto interno e \n"<<dot(r1,r2) <<"\n";

    
    
    r1.x()=1+3;
    Vec3d r4(-1,-1,-1);
    //escreve no ecran
    cout<<"o r1 e \n" <<r1 <<"\n";  
    cout<<"o r4 e \n" <<r4 <<"\n";  
    cout<<"a soma dos r1 e r4 e \n" <<r1+r4 <<"\n";  
    cout<<"o produto interno e \n"<<dot(r1,r4) <<"\n";


    cout<<"a negação do vetor é \n" <<!r1 << "\n";

    
      
   
      
    return  0;

    
    
    
}

