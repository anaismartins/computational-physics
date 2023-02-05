#include "FCmatrix.h"
#include "FCmatrixFull.h"
#include "FCmatrixAlgorithm.h"
#include <iomanip>
#include <cmath>

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
  }

  // Jordan
  for (int i = nRow - 1; i > 0; i--){
    for (int j = i - 1; j >= 0; j--){
      x = -(D[j][i]/D[i][i]);
      D[j] += D[i]*(x);
      I[j] += I[i]*(x);
    }
  }
  
  // Normalizacao
  for (int i = 0; i < nRow; i++){
    x = 1./D[i][i];
    D[i] *= x;
    I[i] *= x;    
  }

  return I;

}


pair<FCmatrixFull, FCmatrixFull> FCmatrixAlgorithm::LUdecomposition(FCmatrixFull& A){

  FCmatrixFull L = FCmatrixFull(A);
  vector<double> lambda;

  for (int i= 0; i < A.GetRowN(); i++){
    L[i][i] = 1;
    for (int j = 0; j < A.GetRowN(); j++){
      if (i < j)
        L[i][j] = 0;
    }
  }

  FCmatrixFull U = GaussElimination(A);

  for (int i = 1; i< A.GetRowN(); i++){
    L[i][0] = A[i][0]/U[0][0];
    for (int j = 1; j < A.GetRowN(); j++)
      if (j != i){
        double sum;
        for (int k = 0; k < j; k++)
          sum = L[i][k] * U[j][k];
        L[i][j] = (A[i][j] - sum) / U[j][j];
      }
  }

  std::pair<FCmatrixFull, FCmatrixFull> LU;

  LU.first = L;
  LU.second = U;

  return LU;

}
