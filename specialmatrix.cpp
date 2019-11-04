//
// Created by Dzmitry Korshakevich on 21.10.2019.
//

#include <iostream>
#include "specialmatrix.h"

SpecialMatrix::SpecialMatrix(size_t n, bool random)
    : Matrix(n, random) {
  for (size_t i = 0; i < data_.size(); i++) {
    for (size_t j = i + 2; j < data_.size(); j++) {
      data_[i][j] = 0;
    }
  }
}

void SpecialMatrix::Inverse(bool fast) {
  // Вектор, в котором для каждой строки мы храним позицию, до которой
  // встречаются ненулевые элементы
  std::vector<size_t> max_len(data_.size());

  if (fast) {
    for (size_t i = 0; i < max_len.size(); i++) {
      max_len[i] = std::min(i + 1, data_.size() - 1);
    }
  } else {
    for (size_t& i : max_len) {
      i = data_.size() - 1;
    }
  }

  matrix answer(data_.size(), std::vector<double>(data_.size(), 0));

  for (size_t i = 0; i < data_.size(); i++) {
    answer[i][i] = 1;
  }

  for (size_t i = 0; i < data_.size(); i++) {
    // Если на диагонали оказался нулевой элемент
    if (std::abs(data_[i][i]) < kEps) {
      bool found_non_zero = false;
      for (size_t j = i + 1; j < data_.size() && !found_non_zero; j++) {
        if (std::abs(data_[j][i]) > kEps) {
          std::swap(data_[i], data_[j]);
          std::swap(answer[i], answer[j]);
          max_len[i] = max_len[j];
          found_non_zero = true;
        }
      }

      if (!found_non_zero) {
        throw std::runtime_error("Inversion of a degenerate matrix.");
      }
    }

    for (size_t j = i + 1; j < data_.size(); j++) {
      max_len[j] = std::max(max_len[j], max_len[i]);
      if (std::abs(data_[j][i]) > kEps) {
        double coefficient = data_[j][i] / data_[i][i];

        data_[j][i] = 0;
        for (size_t k = i + 1; k <= max_len[i]; k++) {
          data_[j][k] -= data_[i][k] * coefficient;
        }

        for (size_t k = 0; k <= max_len[i]; k++) {
          answer[j][k] -= answer[i][k] * coefficient;
        }
      }
    }
  }

  for (size_t i = data_.size() - 1; i >= 1; i--) {
    for (int j = static_cast<int>(i - 1); j >= 0 && max_len[j] >= i; j--) {
      if (std::abs(data_[j][i]) > kEps) {
        double coefficient = data_[j][i] / data_[i][i];
        data_[j][j] -= data_[i][j] * coefficient;

        for (size_t k = 0; k <= data_.size() - 1; k++) {
          answer[j][k] -= answer[i][k] * coefficient;
        }
      }
    }
  }

  for (size_t i = 0; i < data_.size(); i++) {
    for (size_t k = 0; k < data_.size(); k++) {
      answer[i][k] /= data_[i][i];
    }
  }

  data_ = std::move(answer);
}
