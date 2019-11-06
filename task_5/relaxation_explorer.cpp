//
// Created by Dzmitry Karshakevich on 06.11.2019.
//

#include "relaxation_explorer.h"

namespace relaxation_explorer {

void exploreOmega(std::ostream& out, size_t size, double step) {
  double omega = step;

  Relaxation r(omega, size);
  std::vector<double> result;
  while (omega <= 2) {
    r.SetOmega(omega);
    out << r.Solve(&result) << " ";
    omega += step;
  }
  out << std::endl;
}

void generateLists(const std::vector<size_t>& sizes, const char* filename) {
  std::ofstream out(filename);
  for (const auto& item : sizes) {
    exploreOmega(out, item, 0.1);
  }
  out.close();
}

}  // namespace relaxation_explorer
