//
// Created by Dzmitry Karshakevich on 03.11.2019.
//

#ifndef CMA_LUANDLDLT_H
#define CMA_LUANDLDLT_H

#include <vector>

namespace luAndLdlt {

enum class OperationType {
  LU_USUAL,
  LU_SYMMETRIC,
  LDLT_SYMMETRIC
};

double luUsual(size_t size, const std::vector<double>& v);
double luSymmetric(size_t size, const std::vector<double>& v);
double ldltSymmetric(size_t size, const std::vector<double>& v);
void measureTime(size_t max_size, size_t step, const char* filename);

}  // namespace luAndLdlt

#endif //CMA_LUANDLDLT_H
