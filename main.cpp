#include <iostream>
#include <random>

#include "ludecomposition.h"
#include "matrix.h"
#include "specialmatrix.h"
#include "specialMatrixSpeedTest.h"

int main() {
  freopen("matrices.in", "r", stdin);
  std::mt19937 generator;
  std::uniform_real_distribution<> distribution(-1e-7, 1e-7);

  std::cout << "Task 1." << std::endl;

  for (int i = 0; i < 2; i++) {
    SpecialMatrix m;
    std::cin >> m;

    try {
      m.Inverse();
      std::cout << "Reversed matrix:\n" << m << std::endl;
    } catch (std::runtime_error&) {
      std::cout << "The matrix is degenerate" << std::endl;
    }
  }

  std::cout << "Task 2." << std::endl;

  for (int i = 0; i < 2; i++) {
    Matrix m;
    std::cin >> m;

    std::vector<double> b(m.Size());
    for (double& element : b) {
      std::cin >> element;
    }

    LUDecomposition lu = m.GetLU();

    std::cout << "Matrix L:\n" << lu.L() << std::endl;
    std::cout << "Matrix U:\n" << lu.U() << std::endl;
    std::cout << "Permutation vector:\n";

    auto p = lu.P();
    for (size_t element : p) {
      std::cout << element + 1 << ", ";
    }
    std::cout << std::endl;

    auto x = lu.SolveLinearSystem(b);

    std::cout << "System solution:\n";
    for (double& element : x) {
      std::cout << element << " ";
    }
    std::cout << std::endl;

    std::cout << "Making small errors in the input vector: " << std::endl;

    for (int j = 0; j < 3; j++) {
      auto inexact = b;
      for (double& element : inexact) {
        element *= 1 + distribution(generator);
      }

      x = lu.SolveLinearSystem(inexact);
      for (double& element : x) {
        std::cout << std::setprecision(4) << element << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  return 0;
}
