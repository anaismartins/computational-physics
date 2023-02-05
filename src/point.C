#include "point.h"
#include <cstdio>
#include <cmath>

// constructor
point::point(float x, float y) : coo(new float[2] {x, y}) {
  // allocate memory + init values
  printf("constructor called (%p) \n", this);
  //  coo = new float[2];
  //  coo[0] = x;
  //  coo[1] = y;  
}

// destructor
point::~point() {
  // deallocate memory
  printf("destructor called (%p) \n", this);
  delete [] coo;
}

// copy constructor
point::point(const point& other) : coo(new float[2] {other.coo[0], other.coo[1]}) {
  printf("copy constructor called (obj=%p, other=%p) \n", this, &other);
}

// copy assignment
const point& point::operator=(const point& other) {
  printf("copy assignment (operator=) called (obj=%p, other=%p) \n", this, &other);
  if (this != &other) {
    coo[0] = other.coo[0];
    coo[1] = other.coo[1];    
  }
  return *this;
}

// move  
point::point(point&& other) : coo(other.coo) {
    printf("move constructor called (obj=%p, other=%p) \n", this, &other);  
    other.coo = nullptr;
}  

// ============== operators

point point::operator+(const point& p) const {
  printf("[%s]\n", __PRETTY_FUNCTION__);
  return point(coo[0]+p.coo[0], coo[1]+p.coo[1]);
}

point point::operator-(const point& p) const {
  printf("[%s]\n", __PRETTY_FUNCTION__);
  return point(coo[0]-p.coo[0], coo[1]-p.coo[1]);
}

const point& point::operator+=(const point& p) {
  printf("[%s]\n", __PRETTY_FUNCTION__);
  coo[0] += p.coo[0];
  coo[1] += p.coo[1];
  return *this;
}

const point& point::operator/=(float a) {
  printf("[%s]\n", __PRETTY_FUNCTION__);
  coo[0] /= a;
  coo[1] /= a;
  return *this;
}

float point::operator!() {
  printf("[%s]\n", __PRETTY_FUNCTION__);
  return sqrt(pow(coo[0],2.) + pow(coo[1], 2.));
}

float& point::operator[](int n) {
  printf("[%s]\n", __PRETTY_FUNCTION__);  
  return coo[n];
}

const float& point::operator[](int n) const {
  printf("[%s]\n", __PRETTY_FUNCTION__);
  return coo[n];
}


// ============== friends

ostream& operator<<( ostream& s, const point& p) {
  printf("[%s]\n", __PRETTY_FUNCTION__);  
  s << "[" << p.coo[0] << " , " << p.coo[1] << "]";
  return s;
}

point operator*(float k, const point& p) {
  float a = k*p.coo[0];
  float b = k*p.coo[1];  
  return point(a, b);
}

// ==============

void point::PrintObject() {
  printf("[%s]\n", __PRETTY_FUNCTION__);
  this->Print();  
}

void point::Print() {
  printf("[%s]\n", __PRETTY_FUNCTION__);
  cout << *this;
}



void point::Dump() const {
  printf("Dump(): this=%p [%f , %f] (%p)\n", this, coo[0], coo[1], coo);
}
