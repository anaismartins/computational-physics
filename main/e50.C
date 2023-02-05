#include "FCmatrixT.h"

#include <iostream>
using namespace std;

int main() {
  double a[] = {4, -2, 1, 3, 3, -3./2, 1, 0, 3}; // flag = 2
  // define matrix
  FCmatrixT A(a, 3, 3);
  cout << A << endl;
  
  // print element (1,3)
  cout << A[0][2] << endl;
  // change value of element (1,3) and print it
  A[0][2] = 3.;
  cout << A[0][2] << endl;

  cout << A << " flag = " << A.GetFlag() << endl;
  
  //double b[][3] = { {4., -2., 1.}, {3., 3., -3./2}, {1., 0., 3.} };
  double **b = new double* [3];
  for(int i = 0; i<3; i++) {
    b[i] = new double[3];
    for(int j = 0; j<3; j++) {
      b[i][j] = i*10 + j +11;
    }
  }
  FCmatrixT B(b, 3, 3);
  cout << B << " flag = " << B.GetFlag() << endl;

  vector<Vec> c;
  double c1[] = {4, -2, 1};
  c.push_back(Vec(3, c1));
  double c2[] = {3, 3, -3./2};
  c.push_back(Vec(3, c2));
  double c3[] = {1, 0, 3};
  c.push_back(Vec(3, c3));
  FCmatrixT C(c);
  cout << C << " flag = " << C.GetFlag() << endl;
  
  FCmatrixT D(A);
  cout << D << " flag = " << D.GetFlag() << endl;

  FCmatrixT E;
  E = A;
  cout << E << " flag = " << E.GetFlag() << endl;
  
}
