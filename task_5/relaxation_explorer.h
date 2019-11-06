//
// Created by Dzmitry Karshakevich on 06.11.2019.
//

#ifndef CMA_RELAXATIONEXPLORER_H
#define CMA_RELAXATIONEXPLORER_H

#include <cstddef>
#include <iostream>
#include <fstream>

#include "relaxation.h"

namespace relaxation_explorer {

void exploreOmega(std::ostream& out, size_t size, double step = 0.1);
void generateLists(const std::vector<size_t>& sizes, const char* filename);

}  // namespace relaxation_explorer

#endif //CMA_RELAXATIONEXPLORER_H
