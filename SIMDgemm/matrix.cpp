#include <cstdint>
#include <vector>
#include <iostream>
#include <numeric>

#include <x86intrin.h>
#include "matrix.h"

// MULTIPLIERS
// All implementations done with AVX2.

std::vector<uint16_t> uint16_t_2d_m::mult(uint16_t_2d_m &B)
{
    if (columns != B.get_rows())
    {
        std::cerr << "Invalid Dimensions! (rows, cols)\nA: " << rows << ", " << columns << "\nB: " << B.get_rows() << ", " << B.get_columns() << std::endl;
        exit(1);
    }

    std::vector<uint16_t> C(rows * B.get_columns(), 0);
    uint16_t buf[16];
    uint32_t pos;
    for (uint32_t row = 0; row < rows; row++)
    {
        for (uint32_t col = 0; col < B.get_columns(); col++)
        {
            __m256i sum = _mm256_setzero_si256();
            __m256i a = _mm256_setzero_si256();
            __m256i b = _mm256_setzero_si256();
            for (pos = 0; pos + 16 <= columns; pos += 16)
            {

                a = _mm256_loadu_si256((__m256i *)&(matrix[row + pos]));
                b = _mm256_loadu_si256((__m256i *)&(B.get_t()[(col * columns) + pos]));
                sum = _mm256_add_epi16(sum, _mm256_mullo_epi16(a, b));
            }
            _mm256_storeu_si256((__m256i *)buf, sum);
            C[(row * B.get_columns()) + col] = std::accumulate(buf, buf + 16, 0);
            if (pos + 16 == columns)
                continue;

            for (uint32_t remaining = pos; remaining < columns; remaining++)
            {
                uint16_t mult_sum = matrix[row * columns + remaining] * B.get_t()[(col * columns) + remaining];
                C[(row * B.get_columns()) + col] += mult_sum;
            }
        }
    }
    return C;
};

std::vector<uint32_t> uint32_t_2d_m::mult(uint32_t_2d_m &B)
{
    if (columns != B.get_rows())
    {
        std::cerr << "Invalid Dimensions! (rows, cols)\nA: " << rows << ", " << columns << "\nB: " << B.get_rows() << ", " << B.get_columns() << std::endl;
        exit(1);
    }

    std::vector<uint32_t> C(rows * B.get_columns(), 0);
    return C;
};

std::vector<uint64_t> uint64_t_2d_m::mult(uint64_t_2d_m &B)
{
    if (columns != B.get_rows())
    {
        std::cerr << "Invalid Dimensions! (rows, cols)\nA: " << rows << ", " << columns << "\nB: " << B.get_rows() << ", " << B.get_columns() << std::endl;
        exit(1);
    }

    std::vector<uint64_t> C(rows * B.get_columns(), 0);
    return C;
};

std::vector<float> float_2d_m::mult(float_2d_m &B)
{
    if (columns != B.get_rows())
    {
        std::cerr << "Invalid Dimensions! (rows, cols)\nA: " << rows << ", " << columns << "\nB: " << B.get_rows() << ", " << B.get_columns() << std::endl;
        exit(1);
    }

    std::vector<float> C(rows * B.get_columns(), 0);
    return C;
};

std::vector<double> double_2d_m::mult(double_2d_m &B)
{
    if (columns != B.get_rows())
    {
        std::cerr << "Invalid Dimensions! (rows, cols)\nA: " << rows << ", " << columns << "\nB: " << B.get_rows() << ", " << B.get_columns() << std::endl;
        exit(1);
    }

    std::vector<double> C(rows * B.get_columns(), 0);
    return C;
};

// SETTERS
// Allowing you to modify values in a matrix, they edit the transpose simultaconst neously.

void uint16_t_2d_m::set(const int &pos, uint16_t val)
{
    matrix[pos] = val;

    int pos_row = pos / columns;
    int pos_col = pos - (pos_row * columns);
    transpose[pos_col * rows + pos_row] = val;
};

void uint32_t_2d_m::set(const int &pos, uint32_t val)
{
    matrix[pos] = val;

    int pos_row = pos / columns;
    int pos_col = pos - (pos_row * columns);
    transpose[pos_col * rows + pos_row] = val;
};

void uint64_t_2d_m::set(const int &pos, uint64_t val)
{
    matrix[pos] = val;

    int pos_row = pos / columns;
    int pos_col = pos - (pos_row * columns);
    transpose[pos_col * rows + pos_row] = val;
};

void float_2d_m::set(const int &pos, float val)
{
    matrix[pos] = val;

    int pos_row = pos / columns;
    int pos_col = pos - (pos_row * columns);
    transpose[pos_col * rows + pos_row] = val;
};

void double_2d_m::set(const int &pos, double val)
{
    matrix[pos] = val;

    int pos_row = pos / columns;
    int pos_col = pos - (pos_row * columns);
    transpose[pos_col * rows + pos_row] = val;
};

// DO_TRANSPOSE IMPLEMENTATIONS
// @todo: Accelerate do_transpose using SIMD intrinsic loads.

void uint16_t_2d_m::do_transpose()
{
    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            transpose[column + row] = matrix[row + column];
        }
    }
};

void uint32_t_2d_m::do_transpose()
{
    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            transpose[column * rows + row] = matrix[columns * row + column];
        }
    }
};

void uint64_t_2d_m::do_transpose()
{
    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            transpose[column + row] = matrix[row + column];
        }
    }
};

void float_2d_m::do_transpose()
{
    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            transpose[column + row] = matrix[row + column];
        }
    }
};

void double_2d_m::do_transpose()
{
    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            transpose[column + row] = matrix[row + column];
        }
    }
};
