#include "Vandermonde.h"
#include "TAxis.h"
#include "TH1.h"
#include <cmath>

Vandermonde::Vandermonde(){

	MatrixCoefs = FCmatrixFull();
	PolCoefs = Vec();
	fPoly = new TF1();
	gPoints = TGraph();
	n = 0;
	x = nullptr;
	y = nullptr;
	
}

Vandermonde::Vandermonde(unsigned N, double xmin, double xmax, const TF1& fp){

  if (xmin >= xmax)
    throw std::invalid_argument(Form("[%s] xmin >= xmax...!\n", __PRETTY_FUNCTION__));
  
  n = N;
  double deltax = (xmax-xmin)/(n-1); // n-1 intervalos
  x = new double[n];
  y = new double[n];
  vector<Vec> v;
  double coeff[n];
  
  for(int i = 0; i < n; i++) {
    x[i] = xmin + i*deltax;
    y[i] = fp.Eval(x[i]);
    for(int j = 0; j < n; j++) {
      coeff[j] = pow(x[i], j);
    }
    v.push_back(Vec(n, coeff));
  }
  MatrixCoefs = FCmatrixFull(v);

  /////////////////// obter a = PolCoefs
  PolCoefs = Vec(n, 0.);
  FCmatrixFull Inversa(n, n); 
  this->GetInverseMatrix(Inversa);

  Vec Y(n,y);
  PolCoefs = Inversa*Y;
  
  /////////////////// Graph
  this->SetGraphicsPoints();
  /////////////////// PolyFunc
  this->SetPolynomialFunction();

}

Vandermonde::~Vandermonde(){

	if (x != nullptr)
		delete [] x;
	//delete x;
	if (y != nullptr)
		delete [] y;
	//delete y;

	// delete [] fPoly;

}

//////////////////////// getters

const Vec& Vandermonde::GetCoefficients(){
  return PolCoefs;
}

const FCmatrixFull& Vandermonde::GetMatrix(){
  return MatrixCoefs;
}

const double* Vandermonde::GetX(){
  return x;
}

const double* Vandermonde::GetY(){
  return y;
}

void Vandermonde::GetInverseMatrix(FCmatrixFull& I){

  int m = MatrixCoefs.GetRowN();
  int n = MatrixCoefs.GetColN();
  int nRow = I.GetRowN();
  int nCol = I.GetColN();

  if(m!=nRow || n!=nCol)
    throw std::invalid_argument(Form("[%s] matrixs not compatible...!\n", __PRETTY_FUNCTION__));

  I = FCmatrixAlgorithm::GaussJordanElimination(MatrixCoefs);
}

double Vandermonde::GetCoeffError(){
  
  Vec D(PolCoefs);
  Vec b(n, y);
  D = MatrixCoefs * PolCoefs - b;
    
  double E = D.maxAbs();

  return E;
}

//////////////// graphics getters

TGraph& Vandermonde::GetGraphPoints(){
  return gPoints;
}

TF1& Vandermonde::GetPolyFunc(){
  return *fPoly;
}

//////////////// private setters
  
void Vandermonde::SetGraphicsPoints(){
  gPoints = TGraph(n, x, y);
  gPoints.SetMarkerStyle(20);
  gPoints.SetMarkerColor(38);
  gPoints.SetMarkerSize(2);
  gPoints.SetTitle("gPoints");
  gPoints.GetXaxis()->SetTitle("x axis");
  gPoints.GetYaxis()->SetTitle("y axis");
  gPoints.GetXaxis()->CenterTitle();
  gPoints.GetYaxis()->CenterTitle();
}

void Vandermonde::SetPolynomialFunction() {
  fPoly = new TF1("fPoly", Form("pol%d(0)",n-1), x[0], x[n-1]);
  for(int i = 0; i < n; i++) {
    fPoly->SetParameter(i, PolCoefs[i]);    
  }
  fPoly->SetLineColor(kRed+2);
  fPoly->SetLineWidth(2);
  fPoly->SetTitle("fPoly");
}
