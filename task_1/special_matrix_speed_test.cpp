//
// Created by Dzmitry Karshakevich on 03.11.2019.
//

#include <iostream>
#include <map>

#include "special_matrix_speed_test.h"
#include "../matrix.h"
#include "special_matrix.h"
#include "../task_2/lu_decomposition.h"
#include "../task_3/symmetric_matrix.h"
#include "../task_3/ldlt_decomposition.h"

namespace special_matrix_speed_test {

double testTime(size_t size) {
  SpecialMatrix m(size);
  auto time = clock();

  try {
    m.Inverse();
  } catch (std::runtime_error&) {
    std::cerr << "Degenerate matrix!\n";
    // it's okay, continue
  }

  return (clock() - time);
}

void buildTimeList(size_t min_size, size_t max_size, size_t step,
                   const char* filename) {
  freopen(filename, "w", stdout);

  for (size_t i = min_size; i <= max_size; i += step) {
    std::cout << testTime(i) << " ";
    std::cerr << "Iteration " << i << std::endl;
  }
}

}  // namespace special_matrix_speed_test
