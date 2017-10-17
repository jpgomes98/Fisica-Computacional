
#include <iostream>


using namespace std;

void cenasPassadas()
{
  cout << " O passado olha-me de canto. \n Erros cometidos, erros de quem não pensou..." << endl;
}

namespace my_routine
{
  void getUp()
  {
    cout << " Acorda e levanta-te " << endl;
  }

  void fazerCama()
  {
    cout << " Obedece sempre à tua mãe " << endl;
    cout << " Cumpre os teus compromissos e responsabilidades "  << endl;
  }

  void pequenoAlmoco()
  {
    cout << " Prepara algo e come. Não levantes os olhos Evaristo... " << endl;
  }
}

using namespace my_routine;

int main()
{
  getUp();
  fazerCama();
  pequenoAlmoco();

  ::cenasPassadas();
}
