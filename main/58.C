#include "Integrator.h"
#include <iostream>
using namespace std;

int main(){
	
  TF1* f = new TF1("f", "cos(x)", 0, 1);
  Integrator I(f);
  double F = 0.;
  double error = 0.;
  int k = 5;

  for(int j = 1; j<=k; j++){
    I.Trapezoidal(pow(2,j), F, error);
    cout <<"k="<< j << " F=" << F << " error=" << error << endl;
  }

  error = 0.0042;

  I.TrapezoidalAdaptive(F, error);
  cout << "\nF=" << F << " error=" << error << endl;

  return 0;

}
