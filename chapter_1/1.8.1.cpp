#include <iostream>
#include <random>
#include <cassert>

////////////////////////////////////////
void fillMatrix(int* matrix, int rowCount, int colCount)
{
    assert(nullptr != matrix && rowCount > 0 && colCount > 0);
    std::random_device rd;
    std::uniform_int_distribution<int> dist(-9, 9);
    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            matrix[row * colCount + col] = dist(rd);
        }
    }
}

////////////////////////////////////////
void printMatrix(const int* matrix, int rowCount, int colCount)
{
    assert(nullptr != matrix && rowCount > 0 && colCount > 0);
    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            std::cout << matrix[row * colCount + col] << '\t';
        }
        std::cout << '\n';
    }
}

////////////////////////////////////////
void zeroMatrix(int* matrix, int rowCount, int colCount)
{
    // Time: O(n^2)
    // Space: O(1)
    assert(nullptr != matrix && rowCount > 0 && colCount > 0);

    // first pass
    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            if (matrix[row * colCount + col] > 0) {
                matrix[row * colCount + col] += rowCount * colCount;
            }
        }
    }

    // second pass
    for (int row = 0; row < rowCount; ++row) {
        bool foundZero{};
        for (int col = 0; col < colCount; ++col) {
            if (matrix[row * colCount + col] == 0) {
                matrix[row * colCount + col] = col + 1;
                foundZero = true;
            }
        }
        if (foundZero) {
            for (int col = 0; col < colCount; ++col) {
                if (matrix[row * colCount + col] != col + 1) {
                    matrix[row * colCount + col] = 0;
                }
            }
        }
    }

    // third pass
    for (int col = 0; col < colCount; ++col) {
        bool foundIndex{};
        for (int row = 0; row < rowCount; ++row) {
            if (matrix[row * colCount + col] == col + 1) {
                foundIndex = true;
            }
        }
        if (foundIndex) {
            for (int row = 0; row < rowCount; ++row) {
                matrix[row * colCount + col] = 0;
            }
        }
    }

    // fourth pass
    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            if (matrix[row * colCount + col] > 0) {
                matrix[row * colCount + col] -= rowCount * colCount;
            }
        }
    }
}

////////////////////////////////////////
int main(int argc, char** argv)
{
    if (argc > 2) {
        int rowCount{ std::atoi(argv[1]) };
        int colCount{ std::atoi(argv[2]) };

        if (rowCount <= 0 || colCount <= 0) {
            std::cout << "at least one count is invalid\n";
        }
        else {
            int matrix[rowCount * colCount];
            fillMatrix(matrix, rowCount, colCount);

            std::cout << "BEFORE:\n";
            printMatrix(matrix, rowCount, colCount);
            zeroMatrix(matrix, rowCount, colCount);

            std::cout << "\nAFTER:\n";
            printMatrix(matrix, rowCount, colCount);
        }
    }
    else {
        std::cout << "Usage: " << argv[0] << " <#rows> <#cols>\n";
    }
}
