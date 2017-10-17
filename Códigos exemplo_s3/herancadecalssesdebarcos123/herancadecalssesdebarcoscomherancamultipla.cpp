// herancadecalssescombarcos.cpp


/* o primeiro codigo com OOP foi o simula, inventado para
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

             
       // constructor dos metodos
       void anda();
       void leva();
       void setName( const std::string& theName); 
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
       void veleja();
};

// declaracao de outra classe HERDADA
// e ainda os barcos a remos tambem podem remar
class Barcoaremos : public Barco {  
public:     
       void rema();
};


// agora mais complicado com multipla HERANCA
// uma classe mista
class Barcovelaeremos : public Barcoaremos , public Barcoavela{
public:
       void andamais();
};


//define as funcoes, fora das classes porque nos apetece
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

// problema da heranca multipla: heranca em diamante
void Barcovelaeremos::andamais(){
     std::cout<<Barcoaremos::name<<" anda para todo o lado com vela ou remos \n";
}

//comeca a funcao main()
int main(){

    //cria um cao e um gato, objectos ou instancias das sub-classes
    Barcoavela caravela;
    Barcoaremos galera;
    Barcovelaeremos optimist;
    
    // tambem pode nomea-los assim
    caravela.setName("Sagres");
    galera.setName("Athena");
    optimist.Barcoaremos::setName("Lisboa");
    optimist.Barcoavela::setName("Lisboa");
    
    // fa-los fazer coisas
    caravela.anda();
    caravela.leva();
    caravela.veleja();
    
    galera.anda();
    galera.leva();
    galera.rema();
    
    optimist.Barcoaremos::anda();
    optimist.Barcoaremos::leva();
    optimist.Barcoavela::veleja();
    optimist.Barcoaremos::rema();
    optimist.andamais();
    
    
    //termina o programa
    std::cout << "escerva Enter ou Return para continuar";
    std::cin.get();
    return 0;
    
}//fim do main
    
    


