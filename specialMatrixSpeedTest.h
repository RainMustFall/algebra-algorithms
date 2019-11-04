//
// Created by Dzmitry Karshakevich on 03.11.2019.
//

#ifndef CMA_SPECIALMATRIXSPEEDTEST_H
#define CMA_SPECIALMATRIXSPEEDTEST_H

#include <vector>

namespace specialMatrixSpeedTest {

double testTime(size_t size);
void buildTimeList(size_t min_size, size_t max_size, size_t step,
    const char* filename);

}  // namespace specialMatrixSpeedTest

#endif //CMA_SPECIALMATRIXSPEEDTEST_H
