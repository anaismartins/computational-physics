#include "LagrangeInterpolator.h"

LagrangeInterpolator::LagrangeInterpolator(unsigned int fN, const double* fx, const double* fy, const TF1* fF0) :
DataPoints(fN, fx, fy),
F0(nullptr),
cInterpolator(nullptr) {
  if (fF0) F0 = new TF1(*fF0);
  FInterpolator = new TF1("FInterpolator", this, &LagrangeInterpolator::fInterpolator, xmin, xmax, 0);
}

LagrangeInterpolator::~LagrangeInterpolator() {
  if (FInterpolator) delete FInterpolator;
  if (F0) delete F0;
  if (cInterpolator) delete cInterpolator;
}

LagrangeInterpolator::LagrangeInterpolator(const LagrangeInterpolator& LI) :
LagrangeInterpolator(LI.N, LI.x, LI.y, LI.F0) {;}

////////////////////////////////////////// interpolator methods

double LagrangeInterpolator::Interpolate(double xval) const {
  double result = 0.;
  for (int i=0; i<N; ++i) {
    double lx = 1.;
    for (int k=0; k<N; ++k)
      if (i!=k) lx *= (xval - x[k])/(x[i] - x[k]);
    result += y[i]*lx;
  }
  return result;
}

void LagrangeInterpolator::Draw() const {
  DataPoints::Draw();
  FInterpolator->SetLineColor(38);
  FInterpolator->SetLineWidth(4);
  FInterpolator->Draw("same");
}

const TCanvas& LagrangeInterpolator::GetCanvas()  {
  cInterpolator = new TCanvas("cInterpolator","", 0,0,800,600);
  DataPoints::Draw();
  FInterpolator->SetLineColor(38);
  FInterpolator->SetLineWidth(4);
  FInterpolator->Draw("same");
  return *cInterpolator;
}
//////////////////////////////////////// underlying func

void LagrangeInterpolator::SetFunction(const TF1* fF0) {
  if (fF0) F0 = new TF1(*fF0);
}

//////////////////////////////////////// output

std::ostream& operator<< (std::ostream& s, const LagrangeInterpolator& LI) {
  s << "Lagrange Interpolator " << "x:[" << LI.xmin << "," << LI.xmax << "]" << std::endl;
  for (int i=0; i<LI.N; ++i) {
    s << std::fixed << std::setprecision(3)
      << "(" << LI.x[i] << "," << LI.y[i] << ") f(x)=" << LI.Interpolate(LI.x[i]) << " " ;
  }
  s << "\n";
  return s;
}
