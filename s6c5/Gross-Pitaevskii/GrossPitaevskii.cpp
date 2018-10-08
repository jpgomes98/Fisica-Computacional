/**** Resolução da Eq. de Gross-Pitaevskii em D = 2 + 1 ****/
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <sys/stat.h> /* gestão e organização */
#include <sys/types.h>/* de ficheiros criados */
#include <unistd.h>   /* no sistema (.dat)    */
#include <cerrno>     // error handling with C functions
#include <cstring>    // error handling with C functions
#include <clocale>    // definição linguística
#include "Complex.h"

using namespace std;

#define CLEAN_DIR "rm -f data/*.dat"

int main()
{
  /* Parâmetros da rede */
  int npoints     = 128;
  double xymin    = -10;
  double xymax    =  10;
  /* Constantes físicas */
  double gamma    = 0.1;
  double omega    = 0.85;
  double G        = 1000;
  
  /* Step da rede quadrada */
  double h = (xymax - xymin) / ((double) npoints - 1);

  /* Condições fronteira (constantes) */
  Complex front;
  double frontval = 0;
  front = frontval;

  /* Condições iniciais */
  Complex inside;   // válido no interior do quadrado, no instante inicial
  double insideval = 1;
  inside = insideval;
  
  /* Definir a matriz espacial */
  Complex **phi;
  /* Matriz que vai conter os valores de F(phi) - do lado direito da eq. - para cada ponto do espaço */
  Complex **rhs;

  /* Parâmetros temporais - RK3 */
  double t  = 0;
  double dt = 0.1 * h * h;
  int readyToPrint;      // step entre impressões
  int nmax;              // nº de iterações a efetuar

  /* Output - ficheiros e diretório novo */
  ofstream curOutput;
  char filename[200];
  const char *dirname = "data";          // Novo diretório
  setlocale(LC_MESSAGES, "pt_PT.UTF-8"); // Colocar as mensagens em português
  struct stat status = {0};              // Verificar se existe o diretório antes de o criar

  cout << "*** Resolução da Eq. de Gross-Pitaevskii em D = 2 + 1 ***\n\n\n";
  cout << "Parâmetros: " << "Tempo - " << dt << ",\t Espaço - " << h << "\n\n";

  cout << "Introduza o nº de iterações que pretende realizar: ";
  cin >> nmax;
  cout << "\n";

  cout << "Introduza o nº de iterações entre impressões: ";
  cin >> readyToPrint;
    
  cout << "\nInicializando..." << endl;

  /* Rotina de gestão de ficheiros */
  /* Criar novo diretório para guardar os ficheiros criados */
  if(stat(dirname, &status) == -1){     // Verificar se já existe este diretório
    if(mkdir(dirname, ACCESSPERMS) == -1){
      cout << "Erro: " << strerror(errno) << endl;
      return -1;
    }
    else{
      cout << "Novo diretório '" << dirname << "' criado com sucesso." << endl; 
    }
  }
  else{
    /* Limpar do diretório já existente os .dats anteriormente criados */
    if(system(CLEAN_DIR)){
      cout << "Falha na execução da limpeza do diretório. A terminar..." << endl;
      return 1;
    }
  }
 

  /* Inicializar o sistema */
  CreateSquareGrid(phi, npoints);
  CreateSquareGrid(rhs, npoints);
  /* Fronteira */
  SetBoundaries(phi, npoints, front);
  /* Interior */
  SetInside(phi, npoints, inside);
  /* Normalizar */
  Normalize(phi, npoints, h);
  
  cout << "Inicialização terminada!\n" << endl;
  
  /* Inicializar o algoritmo de resolução */
  cout << "A resolver a eq. de Gross-Pitaevskii... \n" << endl;
  for (int k = 0; k < nmax; k++){
    /* Tempo atual */
    t = k * dt;
    
    /* Calcular o lado direito da equação (rhs), para este instante de tempo através da conf. da grid (phi) */
    ComputeFunction(rhs, phi, xymin, h, npoints, gamma, omega, G);
    
    /* Rotina de impressão de dados */
    if ((k % readyToPrint) == 0){
      cout << "\nImprimindo..." << endl;
      sprintf(filename, "%s/wavefunction_%d.dat", dirname, k);
      curOutput.open(filename);
      if (curOutput.is_open()){
	PrintToFile(phi, h, npoints, xymin, curOutput);
	curOutput.close();
      }
      else{
	cout << "Erro: " << strerror(errno) << endl;
      }
      cout << "Impressão concluída\n" << endl;
    }

    /* Proceder à atualização do espaço com base na eq. de Gross-Pitaevskii */
    RefreshTime(phi, rhs, npoints, xymin, h, dt, gamma, omega, G);

    /* Normalizar */
    Normalize(phi, npoints, h);
  }

  cout << "Terminado!" << endl;

  /* Desalocar */

  DestroyGrid(phi, npoints);
  DestroyGrid(rhs, npoints);
  

  return 0;
}
