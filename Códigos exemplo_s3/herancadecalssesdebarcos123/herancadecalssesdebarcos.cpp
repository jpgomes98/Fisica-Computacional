// herancadecalssescombarcos.cpp


/* a primeira linguagem com OOP foi o simula, inventado para
 simulacoes do escoamento em torno de barcos, em 1967 Ole-Johan Dahl 
 e Kristen Nygaard. Dai o nome de classes pois os barcos agrupam-se 
 em classes. Cada barco de uma classe e um objecto. Mas existem 
 sub-classes de barcos, que podem herdar campos e metodos da classe mae. 
 E isto que aqui ilustramos */
 


// precisamos do ficheiro header, iostream para usar cout e cin
#include <iostream>

// presisamos do ficheiro header, string para usarmos strings
#include <string>



// declaracao da classe Barco
// que por convencao tem uma Maiuscula
class Barco{
public:
       
       Barco()  {} //construtor por defeito
       Barco( const std::string theName ); // construtor que da o nome
       
       //metodos
       void anda();
       void leva();
       void setName( const std::string& theName);
       const std::string& getName() const; 
       // passamos por referencia para ser mais rapido
       // evitando criar uma copia desnecessaria
       // e e const para nao estarmos a alterarmos o theName
       
protected: // como e para usar pelas sub-classes nao podfe ser private            
       // atributo ou campo
       std::string name;
             
};



// declaracao da sub-classe Barcoavela
// obs: que HERDA o que a classe Barco faz, mas 
// ainda os barcos a vela tambem podem velejar
// obsobs: e uma classe da outra que e publica, sendo conhecida
// por todos como uma sub-calsse da calsse Barco      
class Barcoavela : public Barco {
public:
       Barcoavela() : Barco() {}
       Barcoavela( const std::string theName ) : Barco(theName) {}
       
       void veleja();
};

// declaracao de outra classe HERDADA
// e ainda os barcos a remos tambem podem remar
class Barcoaremos : public Barco {  
public:     
       void rema();
};





//define as funcoes, fora das classes porque nos apetece
Barco::Barco( const std::string theName ) {
     name = theName;              
}

const std::string& Barco::getName() const {
      return name;
      }

void Barco::setName(const std::string& theName){
     name = theName;
}

void Barco::anda(){
     std::cout<<name<<" anda\n";
}

void Barco::leva(){
     std::cout<<name<<" leva\n";
}

void Barcoavela::veleja(){
     std::cout<<name<<" orca e arriba ao vento \n";
}

void Barcoaremos::rema(){
     std::cout<<name<<" rema com boa cadencia \n";
}


//comeca a funcao main()
int main(){

    //cria um Barcoavela e um Barcoaremos, instancias ou objectos das sub-classes
    Barcoavela caravela("Sagres");
    Barcoaremos galera;
    
    // tambem pode nomea-los assim
    galera.setName("Athena");
    
    // fa-los fazer coisas
    caravela.anda();
    caravela.leva();
    caravela.veleja();
    
    galera.anda();
    galera.leva();
    galera.rema();
    
    std::cout << caravela.getName() << "\n";
    
    //termina o programa
    std::cout << "escerva Enter ou Return para continuar";
    std::cin.get();
    return 0;
    
}//fim do main
    
    


