#include "fv.h"

int* fintv(int n){
  int *v = new int [n];
  return v;
}

int** fintv(int x, int y){
  int **v = new int* [x];
  for(int i=0; i < x; ++i){
    v[i] = new int [y];
    for(int j = 0; j < y; ++j){
      v[i][j] = 1;
    }
  }
  
  return v;
}
