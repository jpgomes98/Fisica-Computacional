// structure.cpp -Script 6.6

#include <cstdlib>
#include <iostream>
#include <fstream>


// define a "structure", adequada 
// a novos tipos de dados, para alem
// dos basicos
struct aluno{
       
       //define os membros da estrutura
       std::string iniciais;
       std::string apelido;
       char genero; 
       unsigned int numero;
       std::string email;
       
       // nao esquecer o ponto e virgula 
       };
       
       
       


int main()
{
    std::ofstream ficheiro("alunos1.txt",std::ios::app);
    
    // cria as novas variaveis
    aluno alu1;
    
    // pede para escrever o iniciais
    std::cout << "de o 1o nome e as eventuais iniciais intermedias do aluno: \n";
    std::getline(std::cin, alu1.iniciais);
    
    // pede para escrever o apelido
    std::cout << "de o apelido do aluno: \n";
    std::cin >> alu1.apelido;
    
    // pede para escrever o genero
    std::cout << "de o genero (m/f) do aluno: \n";
    std::cin >> alu1.genero;

    // pede para escrever o numero
    std::cout << "de o numero do aluno: \n";
    std::cin >> alu1.numero;
 
    // pede para escrever o email
    std::cout << "de o email do aluno: \n";
    std::cin >> alu1.email;

     // escreve o reultado para confereirmos
     std::cout << "a estrutura escrita foi: \n";
     std::cout << "iniciais: ";
     std::cout << alu1.iniciais;
     std::cout << "\napelido: ";
     std::cout << alu1.apelido;
     std::cout << "\ngenero: ";
     std::cout << alu1.genero;
     std::cout << "\nnumero: ";
     std::cout << alu1.numero;
     std::cout << "\nemail: ";
     std::cout << alu1.email;
     std::cout << "\n";
     
     aluno alu2=alu1;
     
     std::cout << "{ " <<alu2.iniciais
     << " , " << alu2.apelido 
     << " , " << alu2.genero
     << " , " << alu2.numero
     << " , " << alu2.email
     << " }\n";
     
     ficheiro << "{ " <<alu2.iniciais
     << " , " << alu2.apelido 
     << " , " << alu2.genero
     << " , " << alu2.numero
     << " , " << alu2.email
     << " }\n";


    
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
