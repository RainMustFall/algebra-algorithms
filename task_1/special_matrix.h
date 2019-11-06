//
// Created by Dzmitry Korshakevich on 21.10.2019.
//

#ifndef CMA_SPECIALMATRIX_H
#define CMA_SPECIALMATRIX_H

#include "../matrix.h"

class SpecialMatrix : public Matrix {
 public:
  SpecialMatrix() = default;
  explicit SpecialMatrix(size_t n, bool random = true);

  void Inverse(bool fast = true);
};


#endif //CMA_SPECIALMATRIX_H
