#include "FCmatrixFull.h"
#include "FCmatrixAlgorithm.h"
#include "TROOT.h"
#include <stdexcept>
#include <cstdio>

//#define DEBUG

FCmatrixFull::FCmatrixFull() {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  flag = 0;
  m = 0;
  n = 0;
}

FCmatrixFull::FCmatrixFull(int m2, int n2){
#ifdef DEBUG
  std::cout << "matrix" << std::endl;
#endif
  /* M = vector<Vec>(m2);
     for(int i = 0; i < m2; i++) M[i] = Vec(n2, 0.);*/
  for(int i = 0; i < m2; i++)
    M.push_back(Vec(n2, 0.));

  m = m2;
  n = n2;

}


FCmatrixFull::FCmatrixFull(const vector<Vec>& v) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  for (int i=0; i<v.size(); ++i) {
    M.push_back(v[i]);   
  }
flag = 3;
m = v.size();
n = v[0].size();
}

FCmatrixFull::FCmatrixFull(const FCmatrixFull& matrix) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif

  M.clear();
  
  for (int i=0; i<matrix.GetRowN(); i++) {
    M.push_back(matrix.M[i]);   
  }
  flag = 4;

  m = matrix.m;
  n = matrix.n;
  
}

/////////////////////////// operators

Vec& FCmatrixFull::operator[] (int i) {
  return M[i];
}

void FCmatrixFull::operator= (const FCmatrixFull& matrix) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (this != &matrix) {
    M.clear();
    for (int i=0; i < matrix.m; ++i) {
      M.push_back(matrix.M[i]);
    }
  }
  m = matrix.m;
  n = matrix.n;
}

FCmatrixFull FCmatrixFull::operator+(const FCmatrixFull& other){

  int other_m = other.GetRowN();
  int other_n = other.GetColN();
  
  if(m != other_m || n != other_n)
    throw std::invalid_argument(Form("[%s]matrixs incompatible!\n", __PRETTY_FUNCTION__));
  FCmatrixFull B(other);
  FCmatrixFull R(m,n);
  
  for (int i = 0; i < m; i++){
      R[i] = M[i] + B[i];
  }

  return R;
}

FCmatrixFull FCmatrixFull::operator-(const FCmatrixFull& other){

  int other_m = other.GetRowN();
  int other_n = other.GetColN();
  
  if(m != other_m || n != other_n)
    throw std::invalid_argument(Form("[%s]matrixs incompatible!\n", __PRETTY_FUNCTION__));
  FCmatrixFull B(other);
  FCmatrixFull R(m,n);
  
  for (int i = 0; i < m; i++){
      R[i] = M[i] - B[i];
  }

  return R;
}

FCmatrixFull FCmatrixFull::operator*(const FCmatrixFull& other){

  int other_m = other.GetRowN();
  int other_n = other.GetColN();
  
  if(n != other_m)
    throw std::invalid_argument(Form("[%s]matrixs incompatible!\n", __PRETTY_FUNCTION__));
  FCmatrixFull B(other);
  FCmatrixFull A(m, other_n);
  
  for (int i = 0; i < m; i++){
    for (int j = 0; j < other_n; j++){
      Vec column = B.GetCol(j);
      A[i][j] = M[i] * column;
    }
  }

  return A;
}

Vec FCmatrixFull::operator*(const Vec& v){

  if(n != v.size())
    throw std::invalid_argument(Form("[%s]matrix and vec incompatible!\n", __PRETTY_FUNCTION__));

  Vec R(m);
  for (int i = 0; i < m; i++){
      R[i] = M[i]*v;
  }
  

  return R;
}

FCmatrixFull FCmatrixFull::operator*(double x){

  FCmatrixFull R(m,n);
  for (int i = 0; i < m; i++){
      R[i] = M[i]*x;
  }
  

  return R;
}

/*Vec FCmatrixFull::operator-(const Vec& v){

  Vec A(m);

  if(n != v.size())
    throw std::invalid_argument(Form("[%s]matrix and vec incompatible!\n", __PRETTY_FUNCTION__));
  else{
    for (int i = 0; i < m; i++)
      A[i] = M[i][0] - v[i];
  }

  return A;

  }*/


////////////////////////// methods

Vec FCmatrixFull::GetRow(int i) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if(i>m)
    throw std::invalid_argument(Form("[%s]index out of bounds...(i=%d N=%d)!\n", __PRETTY_FUNCTION__, i, m-1));
  return (*this)[i];
}

Vec FCmatrixFull::GetCol(int i) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if(i>n)
    throw std::invalid_argument(Form("[%s]index out of bounds...(i=%d N=%d)!\n", __PRETTY_FUNCTION__, i, n-1));
  double a[m];
  for(int j = 0; j < m; j++){
    a[j] = (*this)[j][i];
  }
  return Vec(m, a);
}

double FCmatrixFull::Determinant(){
  
	FCmatrixFull U = FCmatrixAlgorithm::GaussElimination(*this);
	
	double detU = 1;

	for (int i = 0; i < U.n; i++)
		detU *= U[i][i];

	return detU;
}

int FCmatrixFull::GetRowMax(int i){ // ERRADO

  double max = 0;
  int index = 0;

  for (int j = 0; j < m; j++){
    if (abs(M[i][j]) > max){
      max = abs(M[i][j]);
      index = j;
    }
		
  }

  return index;

}


////////////////////////////////// friend methods

Vec operator*(const Vec& v, const FCmatrixFull& M) {

  int n = M.GetColN();
  int m = M.GetRowN();
  if(m != v.size())
    throw std::invalid_argument(Form("[%s]matrix and vec incompatible!\n", __PRETTY_FUNCTION__));
  
  FCmatrixFull A(M);
  Vec B(v);
  
  Vec R(n);
  for (int i = 0; i < n; i++){
    Vec column = A.GetCol(i);
    R[i] = B * column;
  }
  

  return R;

}

FCmatrixFull operator*(double x, const FCmatrixFull& M) {

  int n = M.GetColN();
  int m = M.GetRowN();
  FCmatrixFull A(M);

  FCmatrixFull R(m,n);
  for (int i = 0; i < m; i++){
      R[i] = A[i]*x;
  }
  

  return R;

}
