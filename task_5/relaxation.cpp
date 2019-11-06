//
// Created by Dzmitry Karshakevich on 06.11.2019.
//

#include <numeric>
#include <cmath>
#include <iostream>
#include "relaxation.h"

Relaxation::Relaxation(double omega, size_t size)
    : omega_(omega),
      size_(size) {}

uint32_t Relaxation::Solve(std::vector<double>* x) const {
  std::vector<double> x_cur(size_, 1);
  std::vector<double> x_prev(size_);

  uint32_t iterations = 0;
  while (!CheckStopCriterion(x_cur)) {
    std::swap(x_cur, x_prev);
    ++iterations;

    for (size_t i = 0; i < size_; i++) {
      x_cur[i] = (1. - omega_) * x_prev[i];

      double second_part = 0;

      if (i == 0) {
        second_part = std::accumulate(x_prev.begin() + 1, x_prev.end(), 0.0);
      } else if (i + 1 == size_) {
        second_part = std::accumulate(x_cur.begin(), x_cur.end() - 1, 0.0);
      } else {
        second_part = x_cur.front() + x_prev.back();
      }

      second_part = 1. - second_part;
      second_part *= omega_ / size_;

      x_cur[i] += second_part;
    }
  }

  *x = std::move(x_cur);
  return iterations;
}

bool Relaxation::CheckStopCriterion(const std::vector<double>& x) const {
  double max_norm = 0;

  double sum_elements = std::accumulate(x.begin(), x.end(), 0.);
  max_norm = std::max(std::abs(1. - (sum_elements + (size_ - 1) * x.front())),
                      max_norm);
  max_norm = std::max(std::abs(1. - (sum_elements + (size_ - 1) * x.back())),
                      max_norm);

  for (size_t i = 1; i + 1 < size_; i++) {
    max_norm = std::max(std::abs(1. - (x.front() + x.back() + size_ * x[i])),
                        max_norm);
  }

  return max_norm < kEps;
}

void Relaxation::SetOmega(double omega) {
  omega_ = omega;
}
