#include <cstdio>

int main(){
  printf("short int = %lu\n\
int = %lu\n\
long int = %lu\n\
unsigned int = %lu\n\
float = %lu\n\
double = %lu\n\
long double = %lu\n", sizeof(short int), sizeof(int), sizeof(long int), sizeof(unsigned int), sizeof(float), sizeof(double), sizeof(long double));

  return 0;
}
