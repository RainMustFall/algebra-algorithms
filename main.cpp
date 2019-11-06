#include <iostream>
#include <random>

#include "matrix.h"
#include "task_1/special_matrix.h"
#include "task_1/special_matrix_speed_test.h"
#include "task_2/lu_decomposition.h"
#include "task_3/lu_and_ldlt_speed_test.h"
#include "task_4/tridiagonal_matrix.h"
#include "task_5/relaxation.h"
#include "task_5/relaxation_explorer.h"

// comment or delete this line to skip time measurement
#define PROCEED_LONG_OPERATIONS

void printLine(int length = 10) {
  for (int i = 0; i < length; i++) {
    std::cout << '-';
  }
  std::cout << std::endl;
}

int main() {
  freopen("matrices.in", "r", stdin);
  std::mt19937 generator;
  std::uniform_real_distribution<> distribution(-1e-7, 1e-7);

  printLine();
  std::cout << "Task 1." << std::endl;
  printLine();

  for (int i = 1; i <= 2; i++) {
    std::cout << "Case " << i << std::endl;
    printLine();
    SpecialMatrix m;
    std::cin >> m;

    try {
      m.Inverse();
      std::cout << "Reversed matrix:\n" << m << std::endl << std::endl;
    } catch (std::runtime_error&) {
      std::cout << "The matrix is degenerate" << std::endl << std::endl;
    }
  }

#ifdef PROCEED_LONG_OPERATIONS
  std::cout << "\nMeasuring execution time. Wait a little...\n" << std::endl;
  special_matrix_speed_test::buildTimeList(100, 6800, 100, "task 1.out");
#endif

  printLine();
  std::cout << "Task 2." << std::endl;
  printLine();

  for (int i = 1; i <= 2; i++) {
    std::cout << "Case " << i << std::endl;
    printLine();
    Matrix m;
    std::cin >> m;

    std::vector<double> b(m.Size());
    for (double& element : b) {
      std::cin >> element;
    }

    LuDecomposition lu = m.GetLu();

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

#ifdef PROCEED_LONG_OPERATIONS
  printLine();
  std::cout << "Task 3." << std::endl;
  printLine();
  std::cout << "\nMeasuring execution time. Wait a little...\n" << std::endl;
  lu_and_ldlt_speed_test::measureTime(100, 2000, 100, "task 3.out");
#endif

  printLine();
  std::cout << "Task 4." << std::endl;
  printLine();

  for (int i = 1; i <= 2; i++) {
    TridiagonalMatrix m;
    std::cin >> m;

    std::vector<double> b(m.Size());
    for (double& element : b) {
      std::cin >> element;
    }

    auto x = m.LinearSolve(b);
    std::cout << "Solution #" << i << ":\n";
    for (const auto& item : x) {
      std::cout << item << " ";
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
  printLine();
  std::cout << "Task 5." << std::endl;
  printLine();

  std::vector<size_t> sizes = {500, 1000, 2000, 4000};
  std::vector<double> solution;
  double omega = 1;

  for (const auto& size : sizes) {
    std::cout << "Matrix of size " << size << ":\n";
    Relaxation r(omega, size);
    std::cout << "Solved in " << r.Solve(&solution) << " iterations.\n";

    std::cout << "First 10 components:\n";
    for (size_t i = 0; i < 10; i++) {
      std::cout << solution[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Last 10 components:\n";
    for (size_t i = solution.size() - 10; i < solution.size(); i++) {
      std::cout << solution[i] << " ";
    }
    std::cout << std::endl << std::endl;
  }

#ifdef PROCEED_LONG_OPERATIONS
  relaxation_explorer::generateLists({500, 1000, 2000, 4000}, "task 5.out");
  std::cout << "Numbers of iterations for each omega \n" <<
            "value were written to \"task 5.out\"";
#endif

  return 0;
}
