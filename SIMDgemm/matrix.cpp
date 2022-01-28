#include <cstdint>
#include <vector>
#include <iostream>
#include <x86intrin.h>
#include <immintrin.h>
#include "matrix.h"


// @todo: Accelerate transpose using SIMD intrinsic loads.
void uint16_t_2d_m::transpose() {
    std::vector<uint16_t> temp(matrix.size());
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            temp[column + row] = matrix[row + column];
        }
    }
    matrix = temp;
};

void uint32_t_2d_m::transpose() {
    std::vector<uint32_t> temp(matrix.size());
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            temp[column * rows + row] = matrix[columns * row + column];
        }
    }
    matrix = temp;
};

uint32_t_2d_m::uint32_t_2d_m(int _rows, int _columns) {
    rows = _rows;
    columns = _columns;
    matrix = std::vector<uint32_t> (rows*columns);
}

    void
    uint64_t_2d_m::transpose()
{
    std::vector<uint64_t> temp(matrix.size());
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            temp[column + row] = matrix[row + column];
        }
    }
    matrix = temp;
};

void float_2d_m::transpose() {
    std::vector<float> temp(matrix.size());
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            temp[column + row] = matrix[row + column];
        }
    }
    matrix = temp;
};

void double_2d_m::transpose() {
    std::vector<double> temp(matrix.size());
    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            temp[column + row] = matrix[row + column];
        }
    }
    matrix = temp;
};
