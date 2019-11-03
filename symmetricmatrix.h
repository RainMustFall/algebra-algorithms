//
// Created by Dzmitry Korshakevich on 23.10.2019.
//

#ifndef CMA_SYMMETRICMATRIX_H
#define CMA_SYMMETRICMATRIX_H

#include "matrix.h"

class LDLtDecomposition;

class SymmetricMatrix : public Matrix {
public:
    SymmetricMatrix() = default;

    explicit SymmetricMatrix(size_t n, bool random = true);
    explicit SymmetricMatrix(matrix&& data);

    LDLtDecomposition GetLDLt() const;

    LUDecomposition GetLU() const override;

    std::istream& Read(std::istream& in) override;
    std::ostream& Write(std::ostream& out) const override;

    // Достраивает вторую половинку и возвращает полную матрицу
    Matrix GetFull() const;

private:
    void InitUpperHalf(size_t n, bool random);
};

#endif //CMA_SYMMETRICMATRIX_H
