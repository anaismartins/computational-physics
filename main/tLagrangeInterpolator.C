#include "LagrangeInterpolator.h"
#include "Vec.h"

#include <cmath>
#include "TMath.h"
#include "TApplication.h"
#include "TCanvas.h"

#include <iostream>
using namespace std;

int main() {

  auto f = [](double x) { return sin(TMath::TwoPi()*x) + exp(x) ; };

  // sampling 10 points
  int N = 10;
  Vec vx(N), vy(N);
  double step = 1./N;
  for (int i=0; i<10; ++i) {
    vx[i] = i*step;
    vy[i] = f(vx[i]);
  }
  cout << vx << endl;

  // lagrange interpolator
  LagrangeInterpolator L((unsigned int)vx.size(), vx.data(), vy.data(), nullptr);
  cout << L << endl;

  // graph
  TApplication tapp("app", 0, 0);
  TCanvas *cc = new TCanvas("cc", "", 0,0,1000,800);
  L.Draw();
  cc->Modified();
  cc->Update();
  tapp.Run();

}
