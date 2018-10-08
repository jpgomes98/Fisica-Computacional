#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <complex>
#include <string>
#include "Complex.h"

using namespace std;

int main()
{
  /**** Resolução da Eq. de Gross-Pitaevski em D = 2 + 1 ****/

  /* Parâmetros do espaço 2D */
  int nx = 128, ny = 128;
  double xmin = -10, xmax = 10;
  double ymin = -10, ymax = 10;
  double dx = (xmax - xmin)/((double) nx - 1);
  double dy = (ymax - ymin)/((double) ny - 1);

  /* Constantes físicas */
  double gamma = 0.01;
  double omega = 0.85;
  double G     = 1000;

  /* Condições fronteira (constantes) */
  double front = 0;

  /* Condições iniciais */
  double inside = 1;   // válido no interior do quadrado

  /* Normalização */
  double phiNorm = 1;
  
  /* Definir a matriz espacial */
  Complex **phi1;
  Complex **phi2;
  
  /* Matriz que vai conter os valores de F(phi) - do lado direito da eq. - para cada ponto do espaço */
  Complex **rhs;

  /* Parâmetros temporais - Euler */
  double t  = 0;
  double dt = 0.1 * dx * dy;
  int readyToPrint = 50;

  /* Output */
  ofstream curOutput;
  char filename[200];

  cout << "*** Resolução da Eq. de Gross-Pitaevski em D = 2 + 1 ***\n\n" << endl;
  cout << "Inicializando..." << endl;
  cout << "Parâmetros: " << dt << ",\t" << dx << ",\t" << dy << "\n" << endl;

  /* Alocar o espaço necessário */
  phi1 = new Complex*[nx];
  phi2 = new Complex*[nx];
  rhs  = new Complex*[nx];
  for (int i = 0; i < nx; i++){
    phi1[i] = new Complex[ny];
    phi2[i] = new Complex[ny];
    rhs[i]  = new Complex[ny];
  }

  /* Inicializar o sistema */
  /* Fronteira */
  for (int i = 0; i < nx; i++){
    phi1[i][0] = front;
    phi1[i][ny - 1] = front;
    phi2[i][0] = front;
    phi2[i][ny - 1] = front;
    rhs[i][0] = front;
    rhs[i][ny - 1] = front;
  }
  for (int j = 0; j < ny; j++){
    phi1[0][j] = front;
    phi1[nx - 1][j] = front;
    phi2[0][j] = front;
    phi2[nx - 1][j] = front;
    rhs[0][j] = front;
    rhs[nx - 1][j] = front;
  }

  /* Interior */
  for (int i = 1; i < (nx - 1); i++){
    for (int j = 1; j < (ny - 1); j++){
      phi1[i][j] = inside;
      phi2[i][j] = inside;
    }
  }

  /* Fase final da inicialização do sistema */
  normalize(phi1, nx, ny, dx, dy);
  normalize(phi2, nx, ny, dx, dy);

  cout << "Inicialização terminada!" << endl;
  
  /* Inicializar o algoritmo de resolução */

  cout << "A resolver a eq. de Gross-Pitaevski... \n" << endl;
  
  for (int k = 0; k < 1000; k++){
    t = k * dt;
    /* Calcular o lado direito da equação */
    spaceGP(rhs, phi1, xmin, ymin, dx, dy, nx, ny, gamma, omega, G);
    for (int i = 1; i < (nx - 1); i++){
      for (int j = 1; j < (ny - 1); j++){
	/* Passo temporal com RK3 */
	phi2[i][j] = timeGP(phi1, xmin, ymin, dx, dy, dt, i, j, gamma, omega, G);
      }
    }
    
    /* Normalizar */
    normalize(phi2, nx, ny, dx, dy);

    /* Rotina de impressão de dados */
    if (((k % readyToPrint) == 0) && (k != 0)){
      cout << "\nImprimindo..." << endl;
      sprintf(filename, "dadosGPE_t%d.dat", k);
      curOutput.open(filename);
      printToFile(phi2, dx, dy, nx, ny, xmin, ymin, curOutput);
      curOutput.close();
      cout << "Impressão concluída\n" << endl;
    }
    
    /* Atualizar o espaço */
    swapSpace(phi2, phi1, nx, ny);
    //cout << "Iter: " << k << endl;

  }

  cout << "Terminado!" << endl;

  /* Desalocar */

  for(int i = 0; i < nx; i++){
    delete[] phi1[i];
    delete[] phi2[i];
    delete[] rhs[i];
  }

  delete[] phi1;
  delete[] phi2;
  delete[] rhs;
  

  return 0;
}
