#include <iostream>
#include <cmath>
using namespace std;

double Sum(int* vi, int* vj){
  double soma = 0;

  for(int i = vi[0]; i <= vi[1]; i++){
      for(int j = vj[0]; j <= vj[1]; j++){
	soma += cos(i*i + sqrt(j));
      }
  }

  return soma;
}

int main(){
  int vi[2] = {0, 100};
  int vj[2] = {5, 300};

  cout << "A soma é igual a " << Sum(vi, vj) << endl;
  
  return 0;
}
