#ifndef __Vec__
#define __Vec__

#include <iostream> // ostream

class Vec {

 public:

  // constructors
  Vec(int i=0, double x=0); // Vec v;
  Vec(int, const double*);
  Vec(const Vec&);

  // destructor
  ~Vec();

  // operators
  double  operator[](int i) const;
  double& operator[](int i);

  void operator=(const Vec&); // A=B
  const Vec& operator+=(const Vec&);
  Vec operator+(const Vec&);
  const Vec& operator-=(const Vec&);
  Vec operator-(const Vec&);
  const Vec& operator*=(double);
  Vec operator*(double) const; //Vec.operator*(double) <=> A*5.
  Vec operator*(Vec) const;
  //Vec& operator/= (double);
  Vec operator/(double) const;
  
  // additional methods
  void SetEntries (int, double*);
  double dot(const Vec&); // double result = a.dot(b)
  void swap(int, int);
  int size() const;
  double sumAbs();
  int At(int);
  double maxAbs();
  double* data();
  
  // friend methods
  friend std::ostream& operator<<(std::ostream&, const Vec&);
  //  friend Vec operator*(double, const Vec&); // 5*A
  friend void swap(Vec&, Vec&);

  // Print
  virtual void Print();
  
 private:
  int N; // number of elements
  double *entries; // array
  
};
#endif
