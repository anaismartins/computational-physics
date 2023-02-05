#include "FCmatrixT.h"
#include <iostream>
using namespace std;

int main() {

  cout << "============ default constructor" << endl;
  FCmatrixT Ma;
  cout << Ma << endl;

  cout << "============ constructor double** " << endl;
  int m=5; // nb of rows
  int n=4;
  double **a = new double*[m];
  a[0] = new double[n] {1,2,3,4};
  a[1] = new double[n] {11,12,13,14};
  a[2] = new double[n] {21,22,23,24};
  a[3] = new double[n] {31,32,33,34};
  a[4] = new double[n] {41,42,43,44};  
  FCmatrixT Mb(a, m, n);
  cout << Mb << endl;
  
  cout << "============ constructor double* " << endl;
  m=3; // nb of rows
  n=3;
  double *c = new double[m*n] {1,2,3,4,5,6,7,8,9};
  FCmatrixT Mc(c, m, n);
  cout << Mc << endl;

  cout << "============ copy constructor " << endl;  
  FCmatrixT Md(Mc);
  cout << Md << endl;
  
}