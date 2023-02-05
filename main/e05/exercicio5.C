#include <cstdio>
#include <limits>

int main(){
  printf("int [%d, %d]\n\
unsigned int [%d, %u]\n\
float [%f, %f]\n\
double [%f, %f]\n", std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), std::numeric_limits<unsigned int>::min(), std::numeric_limits<unsigned int>::max(), std::numeric_limits<float>::min(), std::numeric_limits<float>::max(), std::numeric_limits<double>::min(), std::numeric_limits<double>::max());

  return 0;
}
