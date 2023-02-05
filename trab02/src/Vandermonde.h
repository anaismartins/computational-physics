#include "TF1.h"
#include "Vec.h"
#include "FCmatrix.h"
#include "FCmatrixFull.h"
#include "TGraph.h"

class Vandermonde {

public:

// construtors, destructor
Vandermonde();
Vandermonde(unsigned, double, double, const TF1&);
~Vandermonde();

// getters

const Vec& GetCoefficients();
const FCmatrixFull& GetMatrix();
const double* GetX();
const double* GetY();
double GetCoeffError();
void GetInverseMatrix(FCmatrixFull&);

// graphics getters
TGraph& GetGraphPoints(); // return data points graph
TF1& GetPolyFunc(); // return polynomial function

private:
// setters
void SetGraphicsPoints(); // set graphics with data points
void SetPolynomialFunction(); // set polynomial TF1 function

// data members
FCmatrixFull MatrixCoefs; //coeff matrix (C)
Vec PolCoefs; // polynomial coeffs (a)

TF1* fPoly; // polynomial function
TGraph gPoints; // point's graphics

int n; // number of points
double* x;
double* y;

};