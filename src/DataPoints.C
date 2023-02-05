#include "DataPoints.h"

#include <stdexcept>
#include <algorithm>
#include <iomanip> // setprecision()

#include "TROOT.h"
#include "TAxis.h"

//constructors
DataPoints::DataPoints() :
  N(0), // nb of elements = 0
  x(nullptr), y(nullptr), // set null pointers
  gPoints(nullptr) {};

DataPoints::DataPoints(unsigned int fN, const double* fx, const double* fy) : N(fN), x(new double[N]), y(new double[N]) {
  // manage wrong args
  if (!fx || !fy)
    throw std::invalid_argument(Form("[%s] null arrays!!!", __PRETTY_FUNCTION__));
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif

  // copy arrays
  std::copy(fx, fx+N, x);
  std::copy(fy, fy+N, y);

  //retrieve min and max values
  SetMinMaxX();
  SetMinMaxY();

  // create graph
  gPoints = new TGraph(N, x, y);
  gPoints->SetMarkerStyle(20);
  gPoints->SetMarkerColor(kRed+2);
  gPoints->SetMarkerSize(1.5);

  gPoints->GetXaxis()->SetRangeUser(0.9*xmin, 1.1*xmax);
  gPoints->GetYaxis()->SetRangeUser(0.9*ymin, 1.1*ymax);
}

DataPoints::~DataPoints() {
}

////////////////////////////////////////// graphics

void DataPoints::Draw() const {
  gPoints->Draw("AP");
}

const TGraph& DataPoints::GetGraph() const {
  return *gPoints;
}

void DataPoints::SetMinMaxX() {
  auto it = std::minmax_element(x, x+N);
  xmin = *it.first;
  xmax = *it.second;
}

void DataPoints::SetMinMaxY() {
  auto it = std::minmax_element(y, y+N);
  ymin = *it.first;
  ymax = *it.second;
}
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif

//////////////////////////////////////// output

void DataPoints::Print(std::string FILE) {}

std::ostream& operator<< (std::ostream& s, const DataPoints& D) {
  s << "Nb points stored: " << D.N << std::endl;
  for (int i=0; i<D.N; ++i) {
    s << std::fixed << std::setprecision(3)
      << "(" << D.x[i] << "," << D.y[i] << ")" ;
  }
  return s;
}
