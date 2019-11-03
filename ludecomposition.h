//
// Created by Dzmitry Korshakevich on 21.10.2019.
//

#ifndef CMA_LUDECOMPOSITION_H
#define CMA_LUDECOMPOSITION_H

#include "matrix.h"

class LUDecomposition {
 public:
  LUDecomposition(Matrix , std::vector<size_t> );
  Matrix L() const;
  Matrix U() const;
  const std::vector<size_t>& P() const;

  std::vector<double>  SolveLinearSystem(const std::vector<double>& b);

 private:
  Matrix lu_;
  std::vector<size_t> p_;
};

#endif //CMA_LUDECOMPOSITION_H
