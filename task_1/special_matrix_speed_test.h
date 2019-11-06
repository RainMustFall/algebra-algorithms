//
// Created by Dzmitry Karshakevich on 03.11.2019.
//

#ifndef CMA_SPECIALMATRIXSPEEDTEST_H
#define CMA_SPECIALMATRIXSPEEDTEST_H

#include <vector>

namespace special_matrix_speed_test {

double testTime(size_t size);
void buildTimeList(size_t min_size, size_t max_size, size_t step,
    const char* filename);

}  // namespace special_matrix_speed_test

#endif //CMA_SPECIALMATRIXSPEEDTEST_H
