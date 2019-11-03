//
// Created by Dzmitry Korshakevich on 26.10.2019.
//

#ifndef CMA_TRIDIAGONALMATRIX_H
#define CMA_TRIDIAGONALMATRIX_H

#include "matrix.h"

class TridiagonalMatrix {
 public:
  TridiagonalMatrix() = default;
  explicit TridiagonalMatrix(size_t n, bool random = true);

  size_t Size() const;
  std::vector<double> LinearSolve(const std::vector<double>& b);

  virtual std::istream& Read(std::istream& in);
  virtual std::ostream& Write(std::ostream& out) const;

 private:
  size_t size_;
  const size_t kOutputWidth = 10;
  const double kEps = 1e-10;

  std::vector<double> main_diagonal_;
  std::vector<double> above_diagonal_;
  std::vector<double> below_diagonal_;
};

std::istream& operator>>(std::istream& in, TridiagonalMatrix& rhs);
std::ostream& operator<<(std::ostream& out, const TridiagonalMatrix& rhs);

#endif //CMA_TRIDIAGONALMATRIX_H
