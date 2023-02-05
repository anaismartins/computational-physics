#include "Vec.h"
#include <cstdio>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <iomanip>
#include "TROOT.h"

//#define DEBUG

///////////////////// constructors

Vec::Vec(int i, double x) : N(i) {
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif*/

  if (N<0) throw std::invalid_argument(Form("[%s] received negative number of elements...!\n", __PRETTY_FUNCTION__));
  if (N==0) {
    entries = nullptr;
  } else {
    entries = new double[N];
    std::fill_n(entries, N, x);
  }
}

Vec::Vec(int i, const double* x) : Vec(i) { //c++11 on...
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif*/
  if (x)
    std::copy(x, x+i, entries);
  else  
    throw std::invalid_argument(Form("[%s] null pointer to array...!\n", __PRETTY_FUNCTION__));
}

Vec::Vec(const Vec& v) : Vec(v.N, v.entries) { //c++11 on...
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif*/
}

////////////////////// destructor
Vec::~Vec() {
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif*/
  if (entries) delete [] entries;
}

///////////////////// operators
double Vec::operator[](int i) const {
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif*/
  if (i>=N) 
    throw std::invalid_argument(Form("[%s] index out of bounds...(i=%d N=%d)!\n", __PRETTY_FUNCTION__, i, N));  
  return entries[i];
}

double& Vec::operator[](int i) {
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif*/
  if (i>=N) 
    throw std::invalid_argument(Form("[%s] index out of bounds...(i=%d N=%d)!\n", __PRETTY_FUNCTION__, i, N));  
  return entries[i];
}

void Vec::operator=(const Vec& v) {
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif*/
  if (this != &v) {
    if (v.N != N) {
      N = v.N;
      delete [] entries;
      entries = new double[N];
    }
    std::copy(v.entries, v.entries+N, entries);    
  }
}

const Vec& Vec::operator+= (const Vec& v) { 
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__ );
#endif*/
  if (v.N != N) {
    throw std::invalid_argument(Form("[%s] objects with different size...(N=%d v.N=%d)!\n", __PRETTY_FUNCTION__, N, v.N));        
  }
  for (int i=0; i<N; ++i) {
    entries[i] += v[i];
  }
  return *this;
}

Vec Vec::operator+ (const Vec& v) { 
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif*/
  if (v.N != N) {
    throw std::invalid_argument(Form("[%s] objects with different size...(N=%d v.N=%d)!\n", __PRETTY_FUNCTION__, N, v.N));        
  }
  double result[N];
  for (int i=0; i<N; ++i) {
    result[i] = entries[i] + v[i];
  }
  return Vec(N, result);
}

const Vec& Vec::operator-= (const Vec& v) { 
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif*/
  if (v.N != N) {
    throw std::invalid_argument(Form("[%s] objects with different size...(N=%d v.N=%d)!\n", __PRETTY_FUNCTION__, N, v.N));        
  }
  for (int i=0; i<N; ++i) {
    entries[i] -= v[i];
  }
  return *this;
}

Vec Vec::operator- (const Vec& v) { 
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif*/
  if (v.N != N) {
    throw std::invalid_argument(Form("[%s] objects with different size...(N=%d v.N=%d)!\n", __PRETTY_FUNCTION__, N, v.N));        
  }
  double result[N];
  for (int i=0; i<N; ++i) {
    result[i] = entries[i] - v[i];
  }
  return Vec(N, result);
}

const Vec& Vec::operator*= (double x) { 
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif*/
  if (fabs(x-1.)>=1E-9) {
    for (int i=0; i<N; ++i) {
      entries[i] *= x;
    }
  }
  return *this;
}

Vec Vec::operator*(double x) const {
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif*/
  if (fabs(x-1.)<1E-9)
    return *this;
  double a[N];
  for (int i=0; i<N; ++i) {
    a[i] = entries[i] * x;
  }
  return Vec(N, a);
} 

Vec Vec::operator*(Vec vec) const{
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif*/

  Vec v(N);
  for (int i = 0; i < N; i++)
    v[i] = entries[i] * (vec.entries)[i];

  return v;

}

/*Vec& Vec::operator/= (double x) { 
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (abs(x-1.)>=1E-9) {
    for (int i=0; i<N; ++i) {
      entries[i] /= x;
    }
  }
  return *this;
}*/


Vec Vec::operator/(double x) const {
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif*/
  if (abs(x-1.)<1E-9)
    return *this;
  double a[N];
  for (int i=0; i<N; ++i) {
    a[i] = entries[i] / x;
  }
  return Vec(N, a);
} 

///////////////////// additional methods

void Vec::SetEntries (int n, double* x) {
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif*/
  if (n<0)
    throw std::invalid_argument(Form("[%s] received negative number of elements...!\n", __PRETTY_FUNCTION__));
  else if (x) {
    N = n;
    if (entries) delete [] entries;
    if (N==0)
      entries = nullptr;
    else {
      entries = new double[N];
      std::copy(x, x+n, entries);
    }
  }
  else
    throw std::invalid_argument(Form("[%s] null pointer to array...!\n", __PRETTY_FUNCTION__));
  
}

double Vec::dot(const Vec& v) {
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif*/
  if (v.N != N)
    throw std::invalid_argument(Form("[%s] objects with different size...(N=%d v.N=%d)!\n", __PRETTY_FUNCTION__, N, v.N));
  return std::inner_product(entries, entries+N, v.entries, 0);
}

void Vec::swap(int i, int j) {
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif*/
  if (std::max(i,j)>=N)
    throw std::invalid_argument(Form("[%s] indices out of range...(N=%d max index=%d)!\n", __PRETTY_FUNCTION__, N, std::max(i,j)));
  if (i!=j) std::swap(entries[i], entries[j]);
}


double Vec::sumAbs() { 
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif*/
  // summ of all absolute values
  return std::accumulate(entries, entries+N, 0, [](double accum, double x){return accum+fabs(x);});
}

int Vec::size() const { 
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif*/
  return N;
}

int Vec::At(int i) {
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif*/
  if (i>=N)
    throw std::invalid_argument(Form("[%s] index out of bounds...(i=%d N=%d)!\n", __PRETTY_FUNCTION__, i, N));

  return entries[i];
}

double Vec::maxAbs() {
  // max of elements (absolute value)
  return fabs(*std::max_element(entries, entries+N, [](double x1, double x2){ return fabs(x1) < fabs(x2);}));
}

double* Vec::data() {
  if (entries == nullptr)
    throw std::invalid_argument(Form("[%s] Vec empty...!\n", __PRETTY_FUNCTION__));    

  double* arr = new double [N];
  std::copy(entries, entries+N, arr);
  return arr;
}


///////////////////// friend methods

std::ostream& operator<<(std::ostream& s, const Vec& v) {
  s << "[";
  for (int i=0; i<v.N; ++i) {
    s << std::fixed << std::setprecision(6) << v.entries[i];
    if (i<v.N-1) s << ", ";
  }
  s << "]";
  return s;
}

void swap(Vec& v1, Vec& v2){
/*#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif*/

  for (int i = 0; i < v1.N; i++){
    if ((v1.entries)[i] != (v2.entries[i]))
      std::swap(v1.entries[i], v2.entries[i]);
  }

}


////////////////////// Print

void Vec::Print() {
  std::cout << "[";
  for (int i=0; i<N; ++i) {
    std::cout << std::fixed << std::setprecision(6) << entries[i];
    if (i<N-1) std::cout << ", ";
  }
  std::cout << "]" << std::endl;
}
