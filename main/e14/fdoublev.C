#include "fv.h"

double* fdoublev(int n){
  double *v = new double [n];
  return v;
}

double*** fdoublev(int x, int y, int z){
  double ***v = new double** [x];
  for(int i=0; i < x; ++i){
    v[i] = new double* [y];
    for(int j = 0; j < y; ++j){
      v[i][j] = new double [z];
      for(int k = 0; k < z; ++k){
	v[i][j][k] = 5;
      }
    }
  }
  
  return v;
}
