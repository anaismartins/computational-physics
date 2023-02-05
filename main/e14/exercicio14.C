#include "fv.h"
#include <iostream>
using namespace std;

void print(int**, int x, int y);
void print(double*** v, int x, int y, int z = 20);
void apagar(int **v, int x);
void apagar(double ***v, int x, int y);
   
int main(){
  // retornar uma matriz de inteiros de dimensão 100x50 inicializados a 1
  int** a = fintv(100,50);
  // retornar um tensor de double de dimensão 100x50x20 inicializados a 5.
  double ***b = fdoublev(100, 50, 20);
  double ***c = fdoublev(100, 50);

  cout << "Tensor A:" << endl;
  print(a, 100, 50);
  cout << "Tensor B:" << endl;
  print(b, 100, 50, 20);
  cout << "Tensor C:" << endl;
  print(c, 100, 50);

  apagar(a, 100);
  apagar(b, 100, 50);
  apagar(c, 100, 50);
}

void print(int** v, int x, int y){
  for(int i = 0; i < x; ++i){
    for(int j = 0; j < y; ++j){
      cout << v[i][j] << "   " << flush;
    }
    cout << endl;
  }
}

void print(double*** v, int x, int y, int z){
  for(int i = 0; i < x; ++i){
    for(int j = 0; j < y; ++j){
      for(int k = 0; k < z; ++k){
	cout << v[i][j][k] << "   " << flush;
      }
      cout << endl;
    }
    cout << endl;
  }
}

void apagar(int **v, int x){
  for(int i = 0; i < x; ++i){
    delete[] v[i];
  }
  delete[] v;
}

void apagar(double ***v, int x, int y){
  for(int i = 0; i < x; ++i){
    for(int j = 0; j < y; ++j){
      delete[] v[i][j];
    }
    delete[] v[i];
  }
  delete[] v;
}
      
