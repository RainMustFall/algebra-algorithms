//
// Created by Dzmitry Korshakevich on 21.10.2019.
//

#include "ludecomposition.h"

#include <utility>

LUDecomposition::LUDecomposition(Matrix lu,
                                 std::vector<size_t> p)
    : lu_(std::move(lu)),
      p_(std::move(p)) {}

std::vector<double> LUDecomposition::SolveLinearSystem(
    const std::vector<double>& b) {
  std::vector<double> pb(b.size());
  for (size_t i = 0; i < b.size(); i++) {
    pb[i] = b[p_[i]];
  }

  // Solving Ly = Pb
  for (size_t i = 0; i < b.size(); i++) {
    for (size_t j = i + 1; j < b.size(); j++) {
      pb[j] -= pb[i] * lu_[j][i];
    }
  }

  // Solving Ux = y
  for (size_t i = b.size() - 1; i > 0; i--) {
    for (size_t j = 0; j < i; j++) {
      pb[j] -= pb[i] * lu_[j][i] / lu_[i][i];
    }
  }

  for (size_t i = 0; i < b.size(); i++) {
    pb[i] /= lu_[i][i];
  }

  return pb;
}

Matrix LUDecomposition::L() const {
  Matrix l = lu_;
  for (size_t i = 0; i < l.Size(); i++) {
    l[i][i] = 1;
    for (size_t j = i + 1; j < l.Size(); j++) {
      l[i][j] = 0;
    }
  }

  return l;
}

Matrix LUDecomposition::U() const {
  Matrix u = lu_;
  for (size_t i = 0; i < u.Size(); i++) {
    for (size_t j = 0; j < i; j++) {
      u[i][j] = 0;
    }
  }

  return u;
}

const std::vector<size_t>& LUDecomposition::P() const {
  return p_;
}
