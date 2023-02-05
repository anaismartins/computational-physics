#ifndef __EQ_SOLVER__
#define __EQ_SOLVER__

#include "EqSolver.h"
#include "FCmatrixAlgorithm.h"
#include "TROOT.h"
#include <cstdio>
#include <iostream>

EqSolver::EqSolver() {
    printf("[%s]\n", __PRETTY_FUNCTION__);
}

EqSolver::EqSolver(const FCmatrix& matrix, const Vec& v) {
    printf("[%s]\n", __PRETTY_FUNCTION__);
    (*Mcoeff) = matrix;
    Vconst = v;
}

Vec EqSolver::GaussEliminationSolver(FCmatrixFull& A, Vec& b) {

  int mA = A.GetRowN();
  int nA = A.GetColN();
  int nb = b.size();
  if(mA<nA)
    throw std::invalid_argument(Form("[%s] infinite system...!\n", __PRETTY_FUNCTION__));
  if(mA>nA)////////////////////////////////
    throw std::invalid_argument(Form("[%s] system may be impossible...!\n", __PRETTY_FUNCTION__));
  if(nA!=nb)
    throw std::invalid_argument(Form("[%s] matrixs not compatible...!\n", __PRETTY_FUNCTION__));

  int n = nA;
  
  // matrix [A|b]
  FCmatrixFull Ab(n, n+1);
  for(int i = 0; i<n; i++){
    for(int j = 0; j<n; j++){
      Ab[i][j] = A[i][j];
    }
    Ab[i][n] = b[i];
  }
  
  // get reduced matrix (FCmatrixAlgorithm)
  FCmatrixFull G = FCmatrixAlgorithm::GaussElimination(Ab);
  
  double x[n];
  
  // back substitution to get solution
  for(int i = n-1; i>=0; i--){
    x[i] = G[i][n];
    for(int j = n-1; j>i; j--){
      x[i] -= G[i][j]*x[j];
    }
    x[i] /= G[i][i];
  }

  return Vec(n, x);
}

Vec EqSolver::LUdecompositionSolver(FCmatrixFull& A, Vec& b) {

  int mA = A.GetRowN();
  int nA = A.GetColN();
  int nb = b.size();
  if(mA<nA)
    throw std::invalid_argument(Form("[%s] infinite system...!\n", __PRETTY_FUNCTION__));
  if(nA!=nb)
    throw std::invalid_argument(Form("[%s] matrixs not compatible...!\n", __PRETTY_FUNCTION__));
  int n = nA;

  // get LU (FCmatrixAlgorithm)
  FCmatrixFull LU = FCmatrixAlgorithm::LUdecomposition(A);
  
  double x[n];
  double y[n];

  // forward solution (Ly=b)
  //loop on rows
  for (int k=0; k<n; k++) {
    double sumC = 0.;
    for (int i=0; i<k; i++) {
      sumC += y[i]*LU[k][i];
    }
    y[k] = b[k] - sumC;
  }

  // backward solution (Ux=y)
  //loop on rows
  for (int k=n-1; k>=0; k--) {
    double sumC = 0.;
    for (int i=k+1; i<n; i++) {
      sumC += x[i]*LU[k][i];
    }
    x[k] = (y[k] - sumC)/LU[k][k];
  }

  return Vec(n, x);
}

#endif
