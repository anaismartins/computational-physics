#include "NevilleInterpolator.h"

NevilleInterpolator::NevilleInterpolator(int N, double *x, double *y, TF1* fF0) : DataPoints (N, x, y){
  FInterpolator = new TF1(fF0[0]);
  F0 = new TF1(fF0[0]);
  cInterpolator = new TCanvas();
}

NevilleInterpolator::~NevilleInterpolator(){

}

NevilleInterpolator::NevilleInterpolator(const NevilleInterpolator& NI){
  
  FInterpolator = NI.FInterpolator;
  F0 = NI.F0;
  cInterpolator = NI.cInterpolator;
}

double NevilleInterpolator::Interpolate(double xval) const {
  // Neville algorithm
  double* yp = new double[N];
  for (int i=0; i<N; i++) {
    yp[i] = y[i]; // auxiliar vector
  }
  for (int k=1; k<N; k++) { // use extreme x-values
    for (int i=0; i<N-k; i++) {
      yp[i] = (
	       (xval-x[i+k])*yp[i] -
	       (xval-x[i])*yp[i+1]) / (x[i]-x[i+k]);
    }
  }
  double A = yp[0];
  delete [] yp;
  return A;
}

void NevilleInterpolator::Draw() { 
  /*DataPoints::Draw();
  FInterpolator->SetLineColor(38);
  FInterpolator->SetLineWidth(4);
  FInterpolator->Draw("same");*/

  gPoints->Draw();
  std::cout << "Aqui1" << std::endl;
  //F0.Draw();
  cInterpolator->Update();

  std::cout << "Aqui2" << std::endl;
}

void NevilleInterpolator::SetResolution(int n) const{

  FInterpolator->SetNpx(n);

}

const TCanvas& NevilleInterpolator::GetCanvas(){

  return cInterpolator[0];

}