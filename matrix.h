//
// Created by Dzmitry Korshakevich on 21.10.2019.
//

#ifndef CMA_MATRIX_H
#define CMA_MATRIX_H

#include <iomanip>
#include <vector>
#include <fstream>
#include <ctime>

typedef std::vector<std::vector<double>> matrix;
class LUDecomposition;

class Matrix {
 public:
  Matrix() = default;
  explicit Matrix(matrix&& data);
  explicit Matrix(size_t n, bool random = true);

  virtual std::istream& Read(std::istream& in);
  virtual std::ostream& Write(std::ostream& out) const;

  Matrix& operator*=(const Matrix& rhs);
  std::vector<double>& operator[](size_t index);
  size_t Size() const;

  virtual LUDecomposition GetLU() const;

  const matrix& GetData() const;

protected:
    matrix data_;
    const double kEps = 1e-10;

    const size_t kOutputWidth = 10;
};

std::istream& operator>>(std::istream& in, Matrix& rhs);
std::ostream& operator<<(std::ostream& out, const Matrix& rhs);

#endif //CMA_MATRIX_H
