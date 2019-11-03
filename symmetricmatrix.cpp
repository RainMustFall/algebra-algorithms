//
// Created by Dzmitry Korshakevich on 23.10.2019.
//

#include <cmath>
#include <iostream>
#include "symmetricmatrix.h"
#include "ludecomposition.h"
#include "ldltdecomposition.h"

SymmetricMatrix::SymmetricMatrix(size_t n, bool random) {
  InitUpperHalf(n, random);
}

SymmetricMatrix::SymmetricMatrix(matrix&& data)
  : Matrix(std::move(data)) {}

LUDecomposition SymmetricMatrix::GetLU() const {
  matrix result = GetFull().GetData();
  std::vector<size_t> P(data_.size());

  for (size_t i = 0; i < data_.size(); i++) {
    P[i] = i;
  }

  const size_t size = result.size();
  for (size_t i = 0; i < size; i++) {
    if (std::abs(result[i][i]) < kEps) {
      // Если получился нулевой угловой минор, то придётся считать общим
      // алгоритмом
      return GetFull().GetLU();
    }

    for (size_t j = i + 1; j < size; j++) {
      double coefficient = result[i][j] / result[i][i];
      // Обновляем только верхний треугольник
      for (size_t k = j; k < size; k++) {
        result[j][k] -= result[i][k] * coefficient;
      }

      result[j][i] = coefficient;
    }
  }

  return LUDecomposition(Matrix(std::move(result)), P);
}

LDLtDecomposition SymmetricMatrix::GetLDLt() const {
  // Для ответа храним только верхнетреугольный компонент (L^T)
  matrix result = data_;
  std::vector<double> d(data_.size());
  std::vector<double> buffer(data_.size());

  size_t size = result.size();
  for (size_t i = 0; i < size; i++) {
    if (std::abs(result[i][0]) < kEps) {
      // Если получился нулевой угловой минор, то условия теоремы
      // не выполняются
      throw std::runtime_error("Zero angle minor");
    }

    if (result[i][0] < 0) {
      d[i] = -1;
    } else {
      d[i] = 1;
    }

    double row_divisor = std::sqrt(result[i][0] * d[i]) * d[i];

    for (size_t j = 0; j + i < size; j++) {
      buffer[j] = result[i][j];
      result[i][j] /= row_divisor;
    }

    for (size_t j = 1; i + j < size; j++) {
      double coefficient = buffer[j] / result[i][0];
      // Обновляем только верхний треугольник
      for (size_t k = 0; i + j + k < size; k++) {
        result[i + j][k] -= result[i][k + j] * coefficient;
      }
    }
  }

  return LDLtDecomposition(SymmetricMatrix(std::move(result)), d);
}

Matrix SymmetricMatrix::GetFull() const {
  Matrix result(data_.size(), false);

  for (size_t i = 0; i < data_.size(); i++) {
    for (size_t j = 0; j + i < data_.size(); j++) {
      result[i][j + i] = data_[i][j];
      result[j + i][i] = data_[i][j];
    }
  }

  return result;
}

void SymmetricMatrix::InitUpperHalf(size_t n, bool random) {
  data_ = std::vector<std::vector<double>>(n);
  for (size_t i = 0; i < n; i++) {
    data_[i].resize(n - i);
    for (size_t j = 0; j + i < n; j++) {
      data_[i][j] = random ? rand() % 100 : 0;
    }
  }
}

std::istream& SymmetricMatrix::Read(std::istream& in) {
  size_t n;
  in >> n;

  InitUpperHalf(n, false);

  for (auto& row : data_) {
    for (auto& element : row) {
      in >> element;
    }
  }

  return in;
}

std::ostream& SymmetricMatrix::Write(std::ostream& out) const {
  for (size_t i = 0; i < data_.size(); i++) {
    for (size_t j = 0; j < data_.size(); j++) {
      out.width(kOutputWidth);
      if (j >= i) {
        out << data_[i][j - i] << " ";
      } else {
        out << data_[j][i - j] << " ";
      }
    }
    out << std::endl;
  }

  return out;
}
