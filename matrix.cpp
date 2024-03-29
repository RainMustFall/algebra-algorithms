//
// Created by Dzmitry Korshakevich on 21.10.2019.
//

#include <iostream>

#include "./matrix.h"
#include "task_2/lu_decomposition.h"

Matrix::Matrix(size_t n, bool random)
    : data_(matrix(n, std::vector<double>(n, 0))) {
  if (random) {
    for (auto& line : data_) {
      for (double& element : line) {
        element = rand();
      }
    }
  }
}

Matrix::Matrix(matrix&& data)
        : data_(data) {}

std::istream& Matrix::Read(std::istream& in) {
  size_t n;
  in >> n;

  data_ = matrix(n, std::vector<double>(n));

  for (auto& row : data_) {
    for (auto& element : row) {
      in >> element;
    }
  }
  return in;
}

std::ostream& Matrix::Write(std::ostream& out) const {
  for (const auto& row : data_) {
    for (const auto& element : row) {
      out.width(kOutputWidth);
      out << element << " ";
    }
    out << std::endl;
  }
  return out;
}

std::ostream& Matrix::GenerateLaTeX(std::ostream& out) const {
  out << "\\begin{bmatrix}\n";
  for (const auto& row : data_) {
    for (size_t i = 0; i < row.size(); i++) {
      out << std::setprecision(10) << row[i] << " ";
      if (i + 1 != row.size()) {
        out << "& ";
      } else {
        out << "\\\\\n";
      }
    }
  }
  out << "\\end{bmatrix}\n";
  return out;
}

Matrix& Matrix::operator*=(const Matrix& rhs) {
  matrix answer(data_.size(), std::vector<double>(data_.size(), 0));

  for (size_t i = 0; i < data_.size(); i++) {
    for (size_t j = 0; j < data_.size(); j++) {
      answer[i][j] = 0;
      for (size_t t = 0; t < data_.size(); t++) {
        answer[i][j] += data_[i][t] * rhs.data_[t][j];
      }
    }
  }

  data_ = std::move(answer);
  return *this;
}

LuDecomposition Matrix::GetLu() const {
  Matrix result = *this;
  std::vector<size_t> P(data_.size());

  for (size_t i = 0; i < data_.size(); i++) {
    P[i] = i;
  }

  for (size_t i = 0; i < result.data_.size(); i++) {
    size_t best_index = i;
    for (size_t j = i + 1; j < result.data_.size(); j++) {
      if (std::abs(result[j][i]) > std::abs(result[best_index][i])) {
        best_index = j;
      }
    }

    std::swap(result[i], result[best_index]);
    std::swap(P[i], P[best_index]);

    if (std::abs(result[i][i]) < kEps) {
      throw std::runtime_error("Degenerate matrix.");
    }

    for (size_t j = i + 1; j < result.data_.size(); j++) {
      double coefficient = result[j][i] / result[i][i];
      result[j][i] = coefficient;

      for (size_t k = i + 1; k < result.data_.size(); k++) {
        result[j][k] -= result[i][k] * coefficient;
      }
    }
  }

  return LuDecomposition(result, P);
}

std::vector<double>& Matrix::operator[](size_t index) {
  return data_[index];
}

size_t Matrix::Size() const {
  return data_.size();
}

const matrix& Matrix::GetData() const {
  return data_;
}

std::istream& operator>>(std::istream& in, Matrix& rhs) {
  return rhs.Read(in);
}

std::ostream& operator<<(std::ostream& out, const Matrix& rhs) {
  return rhs.Write(out);
}
