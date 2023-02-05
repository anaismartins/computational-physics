#include "FCmatrixT.h"
#include "FCmatrixAlgorithm.h"

int main() {

  // create matrix 3x3
  const int n = 3;
  double *a[n] {new double[n] {12, -2, 3} ,  new double[n] { -2, 15., 6} , new double[n] {1, 6, 20}};
  FCmatrixT M1(a, n, n);
  cout << M1 << endl; // print matrix

  // make matrix reduction using Gauss elimination
  FCmatrixAlgorithm::GaussElimination(M1);
  cout << M1 << endl; // print reduced matrix
}