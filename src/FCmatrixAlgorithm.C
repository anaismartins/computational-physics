#include "FCmatrix.h"
#include "FCmatrixFull.h"
#include "FCmatrixAlgorithm.h"
#include <iomanip>
#include <cmath>
#include "TROOT.h"

FCmatrixFull FCmatrixAlgorithm::GaussElimination(FCmatrixFull& MR) {
  //printf("[%s]\n", __PRETTY_FUNCTION__);

  FCmatrixFull D = FCmatrixFull(MR);
  double x;

  for (int i=0; i<D.GetRowN()-1; ++i) {
    for (int j=i+1; j<D.GetRowN(); ++j) {
      x = D[j][i]/D[i][i];
      D[j] += D[i]*(-x);
    }
  }

  return D;
}

FCmatrixFull FCmatrixAlgorithm::GaussJordanElimination(FCmatrixFull& MR){

  int nRow = MR.GetRowN();

  FCmatrixFull D = FCmatrixFull(MR);
  FCmatrixFull I = FCmatrixFull(MR);
 
 
  double x;

  // I = Matriz Identidade
  for (int i = 0; i < nRow; i++){
    for (int j = 0; j < nRow; j++)
      if (i == j)
        I[i][j] = 1.;
      else
        I[i][j] = 0.;
  }

  // Ordenação
  double temp;
  for (int i = nRow - 1; i > 0; i--){
    if(D[i -1][0] < D[i][0]){
      for (int j = 0; j < 2 * nRow; j++){
	temp = D[i][j];
	D[i][j] = D[i - 1][j];
	D[i - 1] = temp;
      }
    }
  }
  
  // Gauss
  for (int i=0; i<nRow-1; i++) {
    for (int j=i+1; j<nRow; j++) {
      x = (D[j][i])/(D[i][i]);
      D[j] += D[i]*(-x);
      I[j] += I[i]*(-x);
    }
  D.Print();
  I.Print();
  }

  // Jordan
  for (int i = nRow - 1; i > 0; i--){
    for (int j = i - 1; j >= 0; j--){
      x = -(D[j][i]/D[i][i]);
      D[j] += D[i]*(x);
      I[j] += I[i]*(x);
    }
  D.Print();
  I.Print();
  }
  
  // Normalizacao
  for (int i = 0; i < nRow; i++){
    x = 1./D[i][i];
    D[i] *= x;
    I[i] *= x;    
  }
  
  // std::cout << 2 << '\n';

  return I;
  return I;

}


FCmatrixFull FCmatrixAlgorithm::LUdecomposition(FCmatrixFull& A){

  int m = A.GetRowN();
  int n = A.GetColN();
  if(m!=n)
    throw std::invalid_argument(Form("[%s] matrix with different dimensions...!\n", __PRETTY_FUNCTION__));

  FCmatrixFull LU = GaussElimination(A);

  for (int i = 1; i< n; i++){
    for (int j = 0; j < i; j++){
      double sum = 0;
      for (int k = 0; k < j; k++)
	sum += LU[i][k] * LU[k][j];
      LU[i][j] = (A[i][j] - sum) / LU[j][j];
    }
  }

  return LU;
}
