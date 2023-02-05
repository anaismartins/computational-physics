#ifndef __Gas__
#define __Gas__

#include "TGraph.h"
#include "TF1.h"
#include <vector>
using namespace std;

class Gas{

public:
  Gas(int N, double d, double L, double epsilon, double sigma, double m, double dt); // N, d, L, epsilon, sigma, m, dt
  ~Gas();

  void NextTime();

  // Graphs
  TGraph GetGraphPositions();
  TGraph GetGraphKineticEnergy();
  TGraph GetGraphEnergy();
  TGraph GetGraphVariationEnergy();
  TGraph GetGraphTemperature();
  TGraph GetGraphDesvioQuadratico();

  vector<vector<double>> GetVelocityVector();
  vector<double> GetTemperatureVector();

private:
  double *x;
  double *y;
  double *xA;
  double *yA;
  double *vx;
  double *vy;
  double *ax;
  double *ay;
  double *Fx;
  double *Fy;
  double *Ec;

  TF1 *U;

  // Parametros
  int N;
  double L;
  double epsilon;
  double sigma;
  double m;
  double delta_t;

  // constantes de normalização
  double rc;
  double tc;
  double vc;

  // Plots (t)
  double t;
  double *x0;
  double *y0;
  vector<double> vec_t;
  vector<double> vec_Ec;
  vector<double> vec_E;
  vector<double> vec_dE_relativo;
  vector<double> vec_T;
  vector<double> vec_dQ;

  vector<vector<double>> vec_vel;
  
};

#endif
