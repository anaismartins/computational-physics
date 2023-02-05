#ifndef __FCtools__
#define __FCtools__

#include "Vec.h"
#include <string>
#include <vector>
using namespace std;

class FCtools {
 public:
  /*// retorna o erro relativo de arredondamento
  static double RoundOffError(int i);
  // retorna um objecto TGraph, x = i, y = erro de arredondamento
  static TGraph* RoundOffErrorG(int imin, int imax);
  // retorna um TH1D com a distribuição dos erros de arredondamento
  static TH1D* RoundOffErrorH(int imin, int imax);*/

  //file name, returns lines
  static vector<string> ReadFile2String(string);
  //file name, returns vectors of Vec’s
  static vector<Vec> ReadFile2Vec(string);
  //file name, returns pointer to array of Vec’s, int provides number of lines
  static Vec* ReadFile2Vecp(string, int&);
};

#endif
