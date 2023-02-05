#include "FCmatrix.h"
#include "TROOT.h"

#include <cstdio>
#include <stdexcept>
using namespace std;

//#define DEBUG

FCmatrix::FCmatrix() {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  flag = 0;
  m = 0;
  n = 0;
}

FCmatrix::FCmatrix(double** fM, int fm, int fn) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (!fM)
     throw std::invalid_argument(Form("[%s] null pointer...!\n", __PRETTY_FUNCTION__));
  for (int i=0; i<fm; ++i) {
    if (!fM[i])
      throw std::invalid_argument(Form("[%s] null pointer...!\n", __PRETTY_FUNCTION__));
    M.emplace_back(fn, fM[i]);   
  }
  flag = 1;
  m = fm;
  n = fn;
}

FCmatrix::FCmatrix(double* fM, int fm, int fn) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (!fM)
     throw std::invalid_argument(Form("[%s] null pointer...!\n", __PRETTY_FUNCTION__));
  for (int i=0; i<fm; ++i) {
    M.emplace_back(fn, &fM[i*fn]);
  }
  flag = 2;
  m = fm;
  n = fn;
}

FCmatrix::FCmatrix(const vector<Vec>& v) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  for (int i=0; i<v.size(); ++i) {
    M.emplace_back(v[i]);   
  }
flag = 3;
m = v.size();
n = v[0].size();
}

FCmatrix::FCmatrix(const FCmatrix& matrix) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  for (int i=0; i<matrix.GetRowN(); ++i) {
    M.emplace_back(matrix.M[i]);   
  }
  flag = 4;
  m = matrix.m;
  n = matrix.n;
}

///////////////// methods

int FCmatrix::GetRowN() const {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  return m;  
}

int FCmatrix::GetColN() const {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  return n;  
}

///////////////// DEBUG
int FCmatrix::GetFlag() const {
  return flag;
}

///////////////// operators

void FCmatrix::operator= (const FCmatrix& matrix) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (this != &matrix) {
    M.clear();
    for (int i=0; i< matrix.M.size(); ++i) {
      M.push_back(matrix.M[i]);
    }
  }
  m = matrix.m;
  n = matrix.n;
}

///////////////// friend methods

ostream& operator<< (ostream& s, const FCmatrix& matrix) {
 s << "matrix: [\n";
  for (int i=0; i<matrix.m; ++i) {
    s << "           " << matrix.M[i] << "\n";
  }
  s << "        ]";
 return s;
}


//print method
void FCmatrix::Print(){
  std::cout << "matrix: [\n";
  for (int i = 0; i < n; i++){
    std::cout << M[i] << std::endl;
  }
  std::cout << "        ]\n";
}
