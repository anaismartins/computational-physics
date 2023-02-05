#ifndef __DataPoints__
#define __DataPoints__

#include "TGraph.h"

#include <string>
#include <iostream>
using namespace std;

class DataPoints {

public:

  DataPoints();
  DataPoints(unsigned int, const double*, const double*);
  virtual ~DataPoints();

  virtual double Interpolate(double xval) const {return 0.;};

  // graphics
  virtual void Draw() const;
  virtual const TGraph& GetGraph() const;

  // output
  virtual void Print(std::string FILE="");
  friend ostream& operator<< (ostream&, const DataPoints&);

protected:
  int N; // number of data points
  double *x, *y; // data arrays

  TGraph *gPoints; // graph with data points

  double xmin, xmax;
  double ymin, ymax;

  void SetMinMaxX();
  void SetMinMaxY();

};

#endif
