#include "Vec.h"
#include "FCmatrixT.h"

#include <iostream>

int main() {
  std::cout << "============ throw" << std::endl;
  //  Vec v0(-1); // uncomment if you want to see throw

  std::cout << "============ constructors" << std::endl;
  double a[] = {1.2, 3.0, 5.4, 5.2, 1.0};
  Vec v1(9);
  std::cout << v1 << std::endl;
  Vec v2(10,5.);
  std::cout << v2 << std::endl;
  Vec v3(5, a);
  std::cout << v3 << std::endl;  
  Vec v4(v3);
  std::cout << v4 << std::endl;
  
  std::cout << "============ operator[]" << std::endl;  
  std::cout << v2[3] << std::endl;
  v2[3] = 33.;
  std::cout << v2[3] << std::endl;

  std::cout << "============ operator*" << std::endl;
  Vec v5 = v2*10;
  std::cout << v4 << std::endl;  
/*
  std::cout << "============ dot()" << std::endl;
  auto result = v2.dot(v4);
  std::cout << "result=" << result << std::endl;  */

  std::cout << "============ swap(int, int)" << std::endl;
  std::cout << v2 << std::endl;
  v2.swap(1,7);
  std::cout << v2 << std::endl;  

  std::cout << "============ sumAbs()" << std::endl;
  std::cout << v2.sumAbs() << std::endl;

  // matriz 5x5
  double cm[][5] = {{1., 7., 5., 3., -3.}, {5., 2., 8., -2., 4.}, {1., -5., -4., 6., 7.6}, {0., -5., 3., 3.2, 3.3}, {1., 7., 2., 2.1, 1.2}};
  // array of Vec's for storing matrix rows
  Vec cv[5];

  // copy rows as arrays into Vecs
  for (int i = 0; i < 5; i++)
  	cv[i].SetEntries(5, cm[i]);


}