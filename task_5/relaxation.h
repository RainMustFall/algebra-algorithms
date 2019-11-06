//
// Created by Dzmitry Karshakevich on 06.11.2019.
//

#ifndef CMA_RELAXATION_H
#define CMA_RELAXATION_H

#include <cstddef>
#include <cstdint>
#include <vector>

class Relaxation {
 public:
  Relaxation(double omega, size_t size);
  uint32_t Solve(std::vector<double>* x) const;
  void SetOmega(double omega);

 private:
  const double kEps = 1e-10;
  double omega_;
  size_t size_;

  bool CheckStopCriterion(const std::vector<double>&) const;
};

#endif //CMA_RELAXATION_H
