#include "FCmatrixFull.h"
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

Vec FCmatrixFull::operator*(const Vec& v){

  Vec A(m);

  if(n != v.size())
    throw std::invalid_argument(Form("[%s]matrix and vec incompatible!\n", __PRETTY_FUNCTION__));
  else{
    for (int i = 0; i < m; i++){
      for (int j = 0; j < n; j++)
        A[i] += M[i][j] * v[j];
    }
  }

  return A;
}

Vec FCmatrixFull::operator-(const Vec& v){

  Vec A(m);

  if(n != v.size())
    throw std::invalid_argument(Form("[%s]matrix and vec incompatible!\n", __PRETTY_FUNCTION__));
  else{
    for (int i = 0; i < m; i++)
      A[i] = M[i][0] - v[i];
  }

  return A;

  }

/*Vec& FCmatrixFull::operator[] (int n){

	return (this->M)[n];

}

Vec FCmatrixFull::GetRow(int i){

	return (this->M)[i];

}

Vec FCmatrixFull::GetCol(int i){

	Vec v;

	for (int j = 0; j < this->M.size(); j++)
		v[j] = M[i][j];

}*/

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

	std::pair<FCmatrixFull, FCmatrixFull> LU = FCmatrixAlgorithm::LUdecomposition(*this);

	FCmatrixFull L = FCmatrixFull(LU.first);
	FCmatrixFull U = FCmatrixFull(LU.second);



	double detL = 1, detU = 1, detA;

	for (int i = 0; i < L.n; i++){
		detL = detL * L[i][i];
		detU = detU * U[i][i];
	}

	detA = detU * detL;

	return detA;

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
