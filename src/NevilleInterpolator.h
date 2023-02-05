#ifndef __NevilleInterpolator__
#define __NevilleInterpolator__

#include "DataPoints.h"
#include "TF1.h"
#include "TH1.h"
#include "TCanvas.h"

class NevilleInterpolator : public DataPoints {
  
public:
  // constructors and destructor
  NevilleInterpolator(int N=0, double *x=nullptr, double *y=nullptr,
		      TF1* fF0=nullptr);
  ~NevilleInterpolator();
  
  // copy constructor
  NevilleInterpolator(const NevilleInterpolator&);
  
  // interpolation methods
  double Interpolate(double x) const;
  void Draw(); //draw everything (points and interpolation function)
  void SetResolution(int n=200) const; // deals with SetNpx method of TF1
  const TCanvas& GetCanvas();
  TF1* GetInterpolationFunction() const;
  
  // output
  void Print(string FILE="") const; // print results
  friend ostream& operator<< (ostream&, const NevilleInterpolator&);
  
private:
  double fInterpolator(double *fx, double *par) {
    return Interpolate(fx[0]);
  }
  TF1* FInterpolator; //interpolation function
  TF1* F0; //eventual underlying function
  TCanvas* cInterpolator; // includes data points and curve
};

#endif
