//
// Created by Dzmitry Karshakevich on 03.11.2019.
//

#include <iostream>
#include <map>
#include "../matrix.h"
#include "../Task_2/lu_decomposition.h"
#include "symmetric_matrix.h"
#include "ldlt_decomposition.h"
#include "lu_and_ldlt_speed_test.h"

namespace lu_and_ldlt_speed_test {

double luUsual(size_t size, const std::vector<double>& v) {
  Matrix m(size);
  auto time = clock();
  auto lu = m.GetLu();

  lu.SolveLinearSystem(v);

  return (clock() - time);
}

double luSymmetric(size_t size, const std::vector<double>& v) {
  SymmetricMatrix m(size);
  auto time = clock();
  auto lu = m.GetLu();

  lu.SolveLinearSystem(v);

  return (clock() - time);
}

double ldltSymmetric(size_t size, const std::vector<double>& v) {
  SymmetricMatrix m(size);
  auto time = clock();
  auto lu = m.GetLdlt();

  lu.SolveLinearSystem(v);

  return (clock() - time);
}

void measureTime(size_t min_size, size_t max_size, size_t step,
    const char* filename) {
  freopen(filename, "w", stdout);

  std::map<OperationType, std::vector<double>> time;
  std::vector<double> b;

  for (size_t i = min_size; i <= max_size; i += step) {
    for (size_t j = 0; j < step; ++j) {
      b.push_back(rand());
    }

    time[OperationType::LU_USUAL].push_back(luUsual(i, b));
    time[OperationType::LU_SYMMETRIC].push_back(luSymmetric(i, b));
    time[OperationType::LDLT_SYMMETRIC].push_back(ldltSymmetric(i, b));
    std::cerr << "Iteration " << i << std::endl;
  }

  for (const auto& line : time) {
    for (double i : line.second) {
      std::cout << i << " ";
    }
    std::cout << std::endl;
  }
}

}  // namespace lu_and_ldlt_speed_test
