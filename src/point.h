#ifndef __point__
#define __point__

#include <iostream> // ostream
using namespace std;

// inheritance

class point {

 protected:
  
  float* coo; // pointer 

 public:
  
  point(float x=0., float y=0.); //default constructor
  virtual ~point(); //destructor

  point(const point&); // copy constructor
  const point& operator=(const point&); // copy assignment

  point(point&&); // move constructor
   
  const point& GetObject()  {
    return *this;
  }

  // ------- operators

  point operator+(const point&) const;
  point operator-(const point&) const;
  const point& operator+=(const point&);  
  const point& operator/=(float);    

  float operator!(); // norma sqrt(x^2 + y^2)

  // -------- access operator

  float& operator[](int n); // point P, P[0]=10;
  const float& operator[](int n) const;   
  
  // -------- friends

  friend ostream& operator<<(ostream& s, const point& );
  friend point operator*(float, const point&); // point P2 = 4*P1
  
  // ------- other
  void Dump() const;

  virtual void PrintObject();
  virtual void Print();

};

#endif
