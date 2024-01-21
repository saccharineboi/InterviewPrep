#include <iostream>
#include <random>
#include <cassert>

////////////////////////////////////////
void fillMatrix(int* matrix, int rowCount, int colCount)
{
    assert(nullptr != matrix && rowCount > 0 && colCount > 0);
    std::random_device rd;
    std::uniform_int_distribution<int> dist(1, 9);
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
void zeroMatrix(int* matrix, int rowZero, int colZero, int rowCount, int colCount)
{
    // Time:  O(rowCount + colCount)
    // Space: O(1)
    assert(nullptr != matrix && rowZero >= 0 && colZero >= 0);
    for (int col = 0; col < colCount; ++col) {
        matrix[rowZero * colCount + col] = 0;
    }
    for (int row = 0; row < rowCount; ++row) {
        matrix[row * colCount + colZero] = 0;
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
            printMatrix(matrix, rowCount, colCount);

            while (true) {
                int rowZero{}, colZero{};
                std::cout << "Please enter the coordinates (CTRL+C to quit): ";
                std::cin >> rowZero >> colZero;
                if (rowZero >= 0 && rowZero < rowCount &&
                    colZero >= 0 && colZero < colCount) {
                    zeroMatrix(matrix, rowZero, colZero, rowCount, colCount);
                    printMatrix(matrix, rowCount, colCount);
                }
                else {
                    break;
                }
            }
        }
    }
    else {
        std::cout << "Usage: " << argv[0] << " <#rows> <#cols>\n";
    }
}
