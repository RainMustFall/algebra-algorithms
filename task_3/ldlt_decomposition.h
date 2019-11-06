//
// Created by Dzmitry Korshakevich on 23.10.2019.
//

#ifndef CMA_LTDTDECOMPOSITION_H
#define CMA_LTDTDECOMPOSITION_H

#include <vector>
#include "../matrix.h"
#include "symmetric_matrix.h"

class LdltDecomposition {
 public:
  LdltDecomposition(SymmetricMatrix , std::vector<double> );
  Matrix L() const;
  Matrix D() const;
  Matrix Lt() const;

  std::vector<double>  SolveLinearSystem(const std::vector<double>& b);

 private:
  SymmetricMatrix lt_;
  std::vector<double> d_;
};

#endif //CMA_LTDTDECOMPOSITION_H
