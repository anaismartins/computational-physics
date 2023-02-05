#ifndef __FCmatrix__
#define __FCmatrix__

#include "Vec.h"
#include <vector>
#include <iostream>
#include <utility>
#include <string>
using namespace std;


class FCmatrix {

 public:

  // constructors
  FCmatrix(); // flag=0
  FCmatrix(double** fM, int fm, int fn); //matrix fm x fn, flag=1
  FCmatrix(double* fM, int fm, int fn); // flag=2
  FCmatrix(const vector<Vec>&); // flag=3
  FCmatrix(const FCmatrix&);

  // methods
  int GetRowN() const; // nb of rows
  int GetColN() const; // nb of columns
  // DEBUG
  int GetFlag() const;  

  //virtual methods
  virtual Vec GetRow(int i) = 0; // row i
  virtual Vec GetCol(int i) = 0; // column i
  virtual double Determinant() = 0;
  virtual Vec& operator[](int) = 0;
  //row max element index
  virtual int GetRowMax(int i = 0) = 0;
  //row max element index (scaled by s, from j on)
  //virtual int GetColMax(int j = 0) = 0;

  // operators
  virtual void operator=(const FCmatrix&);
  
  

  // friend methods
  friend ostream& operator<< (ostream& , const FCmatrix& );
  

  // Print
  virtual void Print(); // print matrix (use M3 to do it)
  
protected:
  double** M1;
  double* M2;
  int m; //nb rows
  int n; //nb cols
  int flag; // integer with a definition of which constructor was used
  // store matrix in M3 independently of which constructor is used
  vector<Vec> M3;
  // nb of rows = vector.size()
  // nb of columns = Vec.size() 
  vector<Vec> M;
  
};

#endif
