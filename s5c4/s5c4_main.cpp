#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include "dirent.h"

#include "Matrix.h"

using namespace std;

int main()
{
  double get;
  int y_n;
  
  Matrix G(3, 3);
  Matrix G_inv(3, 3);
  Matrix v(1, 3);
  Matrix u(1, 3);
  Matrix A(2, 4);
  Matrix At(1, 1);

  string toRead("matvec.dat");
  string toWrite("resultados.dat");

  ifstream input;
  ofstream output(toWrite.c_str());
  
  srand(time(NULL));
  
  
  /* Definir os valores da matriz A - aleatório */
  
  for (int i = 1; i <= A.nlin(); i++){
    for (int j = 1; j <= A.ncol(); j++){
      A.set(i, j, floor(((double) rand() / (double) RAND_MAX) * 10)); 
    }
  }
  
  for (int i = 1; i <= v.nlin(); i++){
    v.set(i, 1, floor(((double) rand() / (double) RAND_MAX) * 10));
  }

  u = 1;

  /* Ler os valores de um ficheiro para a matriz G */

  while (1)
    {
      if (checkDir(toRead)){
	input.open(toRead.c_str()); /* associar o stream 'input' ao filename contido no toRead;
				       contudo o ifstream só pode receber (const char*), pelo que 
				       temos de converter a string numa C-string */
	if (input.is_open()){
	  for (int i = 1; i <= G.nlin(); i++){
	    for (int j = 1; j <= G.ncol(); j++){
	      input >> get;
	      G.set(i, j, get);
	    }
	  }
	  break;
	}
      }

      else{
	cout << "O ficheiro com os dados necessários à inicialização não se encontra na  diretória atual." << endl;
	cout << "Pretende especificar um novo ficheiro de leitura? (Sim - 1, Não - 0) " << endl;
	cin >> y_n;
	if (y_n == 1){
	    cout << "Indique o novo ficheiro: ";
	    cin.clear();
	    cin.ignore(80, '\n');
	    getline(cin, toRead);

	  }
	else{
	  cout << "Terminado." << endl;
	  return 1;
	}
      }
    }

  /****************************************************************/

  cout << "Matrix G:" << endl;
  cout << G;
  cout << "det(G): " << G.findDet() << endl;;
  G_inv = G.inverse();
  cout << "Matrix G⁻¹:" << endl;
  cout << G_inv;
  output << G_inv;
  cout << "Matrix A:" << endl;
  cout << A;
  cout << "det(A): " << A.findDet() << endl;
  cout << "Let's transpose A..." << endl;
  At = A.transpose();
  cout << At;
  cout << "[A^T] x [A]" << endl;
  cout << (At * A);
  cout << "Vector v:" << endl;
  cout << v;
  cout << "Vector u:" << endl;
  cout << u;
  cout << "λ(G) = " << G.eigenvalue(u) << "\n" << endl;
  cout << "< u , v > = " << dot(u, v) << "\n" << endl;
  cout << "u x v = " << cross(u, v);

  cout << "Solve linear system represented by Gx = v" << endl;
  cout << "x: " << endl;;
  cout << solve(G, v);


  cout << "[G⁻¹] x [G] = Id" << endl;
  cout << (G*G_inv);

  cout<< u.normalize()<<endl;

 
  return 0;
}
