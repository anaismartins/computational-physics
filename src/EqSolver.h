#ifndef __EqSolver__
#define __EqSolver__

#include "FCmatrixFull.h"
#include "Vec.h"

class EqSolver {

 public:
  EqSolver();
  EqSolver(const FCmatrix&, const Vec&);

  // solvers
  static Vec GaussEliminationSolver(FCmatrixFull&, Vec&); // [A|b]
  static Vec LUdecompositionSolver(FCmatrixFull&, Vec&); // [A|b]

 private:
  FCmatrix *Mcoeff;
  Vec Vconst;
};

#endif
