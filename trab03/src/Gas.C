#include "Gas.h"

#include "TAxis.h"
#include "TH1.h"
#include <algorithm> // min

//////// random v0->theta
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
////////

Gas::Gas(int fN, double d, double fL, double fepsilon, double fsigma, double fm, double dt){

  N = fN;
  L = fL;
  epsilon = fepsilon;
  sigma = fsigma;
  m = fm;
  delta_t = dt;

  rc = sigma;
  tc = rc*sqrt(m/epsilon);
  vc = sqrt(epsilon/m);

  x = new double [N];
  y = new double [N];
  xA = new double [N];
  yA = new double [N];
  x0 = new double [N];
  y0 = new double [N];
  vx = new double [N];
  vy = new double [N];
  ax = new double [N];
  ay = new double [N];
  Fx = new double [N];
  Fy = new double [N];
  Ec = new double [N];

  vec_vel.resize(N);

  // distribuição de 100 partículas, 10 por linha, separadas entre si de d,
  //cujas coordenadas podem ser definidas de acordo com
  for (int i = 0; i < N; i++){
    x0[i] = 6 + d*(i%10);
    y0[i] = 6 + d*int(i/10);
    x[i] = x0[i];
    y[i] = y0[i];
    xA[i] = x0[i];
    yA[i] = y0[i];
  }

  /////////// Potencial
  U = new TF1("Potencial", "4*[0]*(pow(1/x, 12) - pow(1/x, 6))",0,2.5);
  //U = new TF1("Potencial", "4*[0]*(pow([1]/x, 12) - pow([1]/x, 6))",0,2.5);
  U->SetParameter(0, epsilon);
  U->SetParName(0,"epsilon");
  //U->SetParameters(epsilon,sigma);
  //U->SetParNames("epsilon", "sigma");

  double sumU = 0;
  //cálculo das forças no instante inicial e respetiva aceleração
  for (int i = 0; i < N; i++){
    double rx = 0;
    double ry = 0;
    double r = 0;
    double theta = 0;
    Fx[i] = 0;
    Fy[i] = 0;
    for (int j = 0; j < N; j++){
      if(j == i)
	continue;
      rx = x[i]-x[j];
      ry = y[i]-y[j];
      r = sqrt( rx*rx + ry*ry );
      theta = atan2(ry,rx);
      double F = -U->Derivative(r);
      Fx[i] += F*cos(theta);
      Fy[i] += F*sin(theta);
      sumU += U->Eval(r);
    }

    ax[i] = Fx[i];
    ay[i] = Fy[i];

    ////////////////////////////////////////////////////////
    /*if(i == 99){
      cout << "x = " << x[i] << " y = " << y[i] << endl;
      cout << "Fx = " << Fx[i] << " Fy = " << Fy[i] << endl;
      cout << "ax = " << ax[i] << " ay = " << ay[i] << endl;
      }*/
  }

  /////////// Plots
  t = 0;
  vec_t.push_back(t);
  vec_E.push_back(sumU);
  vec_dE_relativo.push_back(1);
  vec_T.push_back(0);
  vec_dQ.push_back(0);

}

/////// destructor
Gas::~Gas(){

  delete [] x;
  delete [] y;
  delete [] xA;
  delete [] yA;
  delete [] vx;
  delete [] vy;
  delete [] ax;
  delete [] ay;
  delete [] Fx;
  delete [] Fy;
  delete [] Ec;

  delete [] x0;
  delete [] y0;
  vec_t.clear();
  vec_Ec.clear();
  vec_E.clear();
  vec_dE_relativo.clear();
  vec_T.clear();
  vec_dQ.clear();

  for(int i = 0; i<vec_vel.size(); i++)
    vec_vel[i].clear();

  vec_vel.clear();
}

void Gas::NextTime(){

  double temp_x = 0;
  double temp_y = 0;
  double temp_r = 0;
  double temp_vx = 0;
  double temp_vy = 0;

  double sumU = 0;
  double sumEc = 0;
  double sumdQ = 0;
  
  for (int i = 0; i < N; i++){

    temp_x = 2*x[i] - xA[i] + delta_t*delta_t * ax[i]; ///////obs: em L -> xA
    temp_y = 2*y[i] - yA[i] + delta_t*delta_t * ay[i];

    temp_vx = (temp_x-xA[i])/(2*delta_t);
    temp_vy = (temp_x-xA[i])/(2*delta_t);

    xA[i] = x[i];
    yA[i] = y[i];
    x[i] = temp_x;
    y[i] = temp_y;

    vx[i] = temp_vx;
    vy[i] = temp_vy;
          
    //while(!(x[i]>=0 && x[i]<=L)){
      if(x[i] >= L){
	x[i] = L - ((int)x[i]%(int)L);
	vx[i] = -vx[i];
      }

      if(x[i] <= 0){
	x[i] = -x[i];
	vx[i] = -vx[i];
      }
      //}
    
      // while(!(y[i]>=0 && y[i]<=L)){
      if(y[i] >= L){
	y[i] = L - ((int)y[i]%(int)L);
	vy[i] = -vy[i];
      }

      if(y[i] <= 0){
	y[i] = -y[i];
	vy[i] = -vy[i];
      }
      // }
      
   double v = sqrt(vx[i]*vx[i] + vy[i]*vy[i]);

    vec_vel[i].push_back(v);

    //cálculo das forças e respetiva aceleração
    double rx = 0;
    double ry = 0;
    double r = 0;
    double theta = 0;
    Fx[i] = 0;
    Fy[i] = 0;
    for (int j = 0; j < N; j++){
      if(j == i)
	continue;
      rx = x[i]-x[j];
      ry = y[i]-y[j];
      r = sqrt( rx*rx + ry*ry );
      theta = atan2(ry,rx);
      double F = -U->Derivative(r);
      Fx[i] += F*cos(theta);
      Fy[i] += F*sin(theta);
      sumU += U->Eval(r);
    }

    ax[i] = Fx[i];
    ay[i] = Fy[i];

     /////////////////////////////////////////////////////
    /*if(i == 99){
      cout << "\nx = " << x[i] << " y = " << y[i] << endl;
      cout << "Fx = " << Fx[i] << " Fy = " << Fy[i] << endl;
      cout << "ax = " << ax[i] << " ay = " << ay[i] << endl;
      }*/
   
    // Plots
    double v2 = vx[i]*vx[i] + vy[i]*vy[i];
    sumEc += 1./2*v2; ///////// m
    sumdQ += ((x[i] - x0[i])*(x[i] - x0[i]) + (y[i] - y0[i])*(y[i] - y0[i]));
  }

  t += delta_t;
  vec_t.push_back(t);
  //E_total
  double E0 = vec_E[0];
  double E = sumEc + sumU; ////////////// Ec*m + U*k ???????????
  double dE = (E - E0)/E0;
  vec_Ec.push_back(sumEc);
  vec_E.push_back(E);
  vec_dE_relativo.push_back(dE);
  vec_T.push_back(sumEc/N);
  vec_dQ.push_back(sumdQ/N);

  
}


////////////////////////////////////////////// GET GRAPHS

TGraph Gas::GetGraphPositions(){
  TGraph gp(N, x, y);
  gp.SetMarkerColor(kBlue);
  gp.SetMarkerSize(1.5);
  gp.SetMarkerStyle(8);
  gp.GetXaxis()->SetLimits(0,L);
  gp.GetHistogram()->SetMinimum(0);
  gp.GetHistogram()->SetMaximum(L);

  return gp;
}

TGraph Gas::GetGraphKineticEnergy(){
  //TGraph ge(vec_t, vec_E);
  int size = min(vec_t.size(),vec_Ec.size());
  TGraph gec(size, vec_t.data(), vec_Ec.data());
  gec.SetTitle("Energia Cinetica");
  //  ge.GetXaxis()->SetTitle("t (s)"); /////// s ??
  
  return gec;
}

TGraph Gas::GetGraphEnergy(){
  //TGraph ge(vec_t, vec_E);
  int size = min(vec_t.size(),vec_E.size());
  TGraph ge(size, vec_t.data(), vec_E.data());
  ge.SetTitle("Energia");
  //  ge.GetXaxis()->SetTitle("t (s)"); /////// s ??
  
  return ge;
}

TGraph Gas::GetGraphVariationEnergy(){
  //TGraph gv(vec_t, vec_dE);
  int size = min(vec_t.size(),vec_dE_relativo.size());
  TGraph gde(size, vec_t.data(), vec_dE_relativo.data());
  gde.SetTitle("Variacao Relativa da Energia"); 
  //  gde.GetXaxis()->SetTitle("t (s)"); /////// s ??
 
  return gde;
}

TGraph Gas::GetGraphTemperature(){
  int size = min(vec_t.size(),vec_T.size());
  TGraph gt(size, vec_t.data(), vec_T.data());
  // gdq.GetXaxis()->SetTitle("t (s)"); /////// s ??
  gt.SetTitle("Temperatura");
  
  return gt;
}

TGraph Gas::GetGraphDesvioQuadratico(){
  int size = min(vec_t.size(),vec_dQ.size());
  TGraph gdq(size, vec_t.data(), vec_dQ.data());
  // gdq.GetXaxis()->SetTitle("t (s)"); /////// s ??
  gdq.SetTitle("Desvio Quadratico");

  return gdq;
}


////////////////////////////////////////////////// GET VECTORS
vector<vector<double>> Gas::GetVelocityVector(){

  return vec_vel;

}

vector<double> Gas::GetTemperatureVector(){

  return vec_T;

}
