#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cstdint>
#include <cassert>

////////////////////////////////////////
void fillMatrix(std::int32_t* matrix, std::int32_t matrixSize)
{
    assert(nullptr != matrix && matrixSize > 0);
    std::random_device rd;
    std::uniform_int_distribution<std::int32_t> dist(0, 9);
    for (std::int32_t row = 0; row < matrixSize; ++row) {
        for (std::int32_t col = 0; col < matrixSize; ++col) {
            matrix[row * matrixSize + col] = dist(rd);
        }
    }
}

////////////////////////////////////////
void printMatrix(const std::int32_t* matrix, std::int32_t matrixSize)
{
    assert(nullptr != matrix && matrixSize > 0);
    for (std::int32_t row = 0; row < matrixSize; ++row) {
        for (std::int32_t col = 0; col < matrixSize; ++col) {
            std::cout << matrix[row * matrixSize + col] << '\t';
        }
        std::cout << '\n';
    }
}

////////////////////////////////////////
void rotateMatrixCCW(std::int32_t* matrix, std::int32_t matrixSize)
{
    // Time: O(n^2) ?
    // Space: O(1)
    assert(nullptr != matrix && matrixSize > 0);
    std::int32_t layerCount{ matrixSize / 2 };
    for (std::int32_t i = 0; i < layerCount; ++i) {
        for (std::int32_t k = i + 1; k < matrixSize - i; ++k) {
            std::int32_t beginRow{i}, beginCol{i};
            std::int32_t endRow{matrixSize - i}, endCol{matrixSize - i};

            std::int32_t tmp{ matrix[beginRow * matrixSize + beginCol] };
            for (; beginCol < endCol - 1; ++beginCol) {
                matrix[beginRow * matrixSize + beginCol] = matrix[beginRow * matrixSize + beginCol + 1];
            }
            for (; beginRow < endRow - 1; ++beginRow) {
                matrix[beginRow * matrixSize + beginCol] = matrix[(beginRow + 1) * matrixSize + beginCol];
            }
            for (; beginCol > i; --beginCol) {
                matrix[beginRow * matrixSize + beginCol] = matrix[beginRow * matrixSize + beginCol - 1];
            }
            for (; beginRow > i + 1; --beginRow) {
                matrix[beginRow * matrixSize + beginCol] = matrix[(beginRow - 1) * matrixSize + beginCol];
            }
            matrix[beginRow * matrixSize + beginCol] = tmp;
        }
    }
}

////////////////////////////////////////
int main(int argc, char** argv)
{
    if (argc > 1) {
        std::int32_t matrixSize{ std::atoi(argv[1]) };
        if (matrixSize <= 0) {
            std::cout << "matrix_size must be a positive integer\n";
        }
        else {
            std::int32_t matrix[matrixSize * matrixSize];
            fillMatrix(matrix, matrixSize);

            std::cout << "ORIGINAL MATRIX:\n";
            printMatrix(matrix, matrixSize);

            std::cout << "MATRIX ROTATED CCW:\n";
            rotateMatrixCCW(matrix, matrixSize);
            printMatrix(matrix, matrixSize);
        }
    }
    else {
        std::cout << "Usage: " << argv[0] << " <matrix_size>\n";
    }
}
