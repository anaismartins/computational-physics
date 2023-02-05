#ifndef __LagrangeInterpolator__
#define __LagrangeInterpolator__

#include "DataPoints.h"

#include "TF1.h"
#include "TCanvas.h"

#include <iostream>

class LagrangeInterpolator : public DataPoints {

 public:
  // constructors and destructor
  LagrangeInterpolator(unsigned int=0, const double* x=nullptr, const double* y=nullptr, const TF1* fF0=nullptr);
  ~LagrangeInterpolator();

  // copy constructor
  LagrangeInterpolator(const LagrangeInterpolator&);

  // interpolation methods
  double Interpolate(double) const;
  const TF1& GetInterpolationFunction() const { return *FInterpolator; }
  void SetResolution(int n=200) const { FInterpolator->SetNpx(n); }
  void Draw() const;
  const TCanvas& GetCanvas();

  // underlying function
  void SetFunction(const TF1*);

  // output
  friend std::ostream& operator<< (std::ostream&, const LagrangeInterpolator&);

 protected:
  TF1* F0; // underlying function
  TF1* FInterpolator; // interpolator function
  TCanvas* cInterpolator;

  double fInterpolator(double *fx, double *par)  {
    return Interpolate(fx[0]);
  }

};

#endif
