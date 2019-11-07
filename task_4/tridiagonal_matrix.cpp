//
// Created by Dzmitry Karshakevich on 26.10.2019.
//


#include "tridiagonal_matrix.h"

TridiagonalMatrix::TridiagonalMatrix(size_t n, bool random)
        : size_(n),
          main_diagonal_(n),
          above_diagonal_(n - 1),
          below_diagonal_(n - 1) {
  if (random) {
    for (size_t i = 0; i + 1 < n; i++) {
      main_diagonal_[i] = rand();
      above_diagonal_[i] = /*0;//*/rand();
      below_diagonal_[i] = rand();
    }
    main_diagonal_[n - 1] = rand();
  } else {
    main_diagonal_.assign(n, 0);
    above_diagonal_.assign(n - 1, 0);
    below_diagonal_.assign(n - 1, 0);
  }
}

std::vector<double> TridiagonalMatrix::LinearSolve(
        const std::vector<double>& b) {
  std::vector<double> solution = b;
  std::vector<double> additional_diag(above_diagonal_.size() - 1, 0);

  size_t n = main_diagonal_.size();
  for (size_t i = 0; i + 1 < n; i++) {
    if (std::abs(main_diagonal_[i]) < std::abs(below_diagonal_[i])) {
      std::swap(main_diagonal_[i], below_diagonal_[i]);
      std::swap(above_diagonal_[i], main_diagonal_[i + 1]);
      std::swap(solution[i], solution[i + 1]);
      if (i + 2 != n) {
        std::swap(additional_diag[i], above_diagonal_[i + 1]);
      }
    }

    if (std::abs(main_diagonal_[i]) < kEps) {
      throw std::runtime_error("degenerate matrix");
    }

    double coefficient = below_diagonal_[i] / main_diagonal_[i];

    below_diagonal_[i] -= main_diagonal_[i] * coefficient;
    main_diagonal_[i + 1] -= above_diagonal_[i] * coefficient;
    solution[i + 1] -= solution[i] * coefficient;

    if (i + 2 != n) {
      above_diagonal_[i + 1] -= additional_diag[i] * coefficient;
    }
  }

  for (size_t i = n - 1; i >= 1; i--) {
    double coefficient = above_diagonal_[i - 1] / main_diagonal_[i];
    solution[i - 1] -= coefficient * solution[i];

    if (i >= 2) {
      coefficient = additional_diag[i - 2] / main_diagonal_[i];
      solution[i - 2] -= coefficient * solution[i];
    }

    solution[i] /= main_diagonal_[i];
  }
  solution[0] /= main_diagonal_[0];

  return solution;
}

std::istream& TridiagonalMatrix::Read(std::istream& in) {
  size_t n;
  in >> n;

  size_ = n;
  above_diagonal_.resize(n - 1);
  main_diagonal_.resize(n);
  below_diagonal_.resize(n - 1);

  for (double& i : above_diagonal_) {
    in >> i;
  }

  for (double& i : main_diagonal_) {
    in >> i;
  }

  for (double& i : below_diagonal_) {
    in >> i;
  }

  return in;
}

std::ostream& TridiagonalMatrix::Write(std::ostream& out) const {
  for (size_t i = 0; i < size_; i++) {
    for (size_t j = 0; j < size_; j++) {
      out.width(kOutputWidth);
      if (j + 1 == i) {
        out << below_diagonal_[i - 1] << " ";
      } else if (j == i) {
        out << main_diagonal_[i] << " ";
      } else if (j == i + 1) {
        out << above_diagonal_[i] << " ";
      } else {
        out << 0;
      }
    }
    out << std::endl;
  }

  return out;
}

size_t TridiagonalMatrix::Size() const {
  return size_;
}

std::istream& operator>>(std::istream& in, TridiagonalMatrix& rhs) {
  return rhs.Read(in);
}

std::ostream& operator<<(std::ostream& out, const TridiagonalMatrix& rhs) {
  return rhs.Write(out);
}
