//
// Created by Dzmitry Korshakevich on 23.10.2019.
//

#include "ldltdecomposition.h"

#include <utility>

LDLtDecomposition::LDLtDecomposition(SymmetricMatrix lt,
                                     std::vector<double> d)
    : lt_(std::move(lt)),
      d_(std::move(d)) {}

Matrix LDLtDecomposition::L() const {
  Matrix result = lt_.GetFull();
  for (size_t i = 0; i < result.Size(); i++) {
    for (size_t j = i + 1; j < result.Size(); j++) {
      result[i][j] = 0;
    }
  }
  return result;
}

Matrix LDLtDecomposition::D() const {
  Matrix result(d_.size(), false);
  for (size_t i = 0; i < d_.size(); i++) {
    result[i][i] = d_[i];
  }
  return result;
}

Matrix LDLtDecomposition::Lt() const {
  Matrix result = lt_.GetFull();
  for (size_t i = 0; i < result.Size(); i++) {
    for (size_t j = 0; j < i; j++) {
      result[i][j] = 0;
    }
  }
  return result;
}

std::vector<double> LDLtDecomposition::SolveLinearSystem(const std::vector<
    double>& b) {
  std::vector<double> result = b;

  // Solving Ly = b
  for (size_t i = 0; i + 1 < b.size(); i++) {
    for (size_t j = i + 1; j < b.size(); j++) {
      result[j] -= result[i] * lt_[i][j - i] / lt_[i][0];
    }
  }

  for (size_t i = 0; i < b.size(); i++) {
    result[i] /= lt_[i][0] * d_[i];
  }

  // Solving L^Tx = y
  for (size_t i = b.size() - 1; i > 0; i--) {
    for (size_t j = 0; j < i; j++) {
      result[j] -= result[i] * lt_[j][i - j] / lt_[i][0];
    }
  }

  for (size_t i = 0; i < b.size(); i++) {
    result[i] /= lt_[i][0];
  }

  return result;
}
