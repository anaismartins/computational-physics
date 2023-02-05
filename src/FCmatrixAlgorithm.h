#ifndef __FCmatrixAlgorithm__
#define __FCmatrixAlgorithm__

#include "FCmatrix.h"
#include "FCmatrixFull.h"

class FCmatrixAlgorithm {

public:

  /*
    Gauss Elimination
    - it can receive a simple matrix
    - linear system: augmented matrix (A | b)
  */

  static FCmatrixFull GaussElimination(FCmatrixFull&);
  static FCmatrixFull GaussJordanElimination(FCmatrixFull&);

  /*
    Gauss Elimination with pivoting
    - it can receive a simple matrix
    - linear system: augmented matrix (A | b)
    - return: (A | b | Index)
  */

  static void GaussEliminationPivot(FCmatrixFull&);

  static FCmatrixFull LUdecomposition(FCmatrixFull&);

};

#endif
