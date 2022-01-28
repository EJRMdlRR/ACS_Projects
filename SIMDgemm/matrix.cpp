#include <cstdint>
#include <vector>
#include <x86intrin.h>
#include <immintrin.h>
#include "matrix.h"

// MULTIPLIERS
std::vector<uint16_t> *uint16_t_2d_m::mult(const std::vector<uint16_t_2d_m> &B) {

};

std::vector<uint32_t> *uint32_t_2d_m::mult(const std::vector<uint32_t_2d_m> &B) {

};

std::vector<uint64_t> *uint64_t_2d_m::mult(const std::vector<uint64_t_2d_m> &B) {

};

std::vector<float> *float_2d_m::mult(const std::vector<float_2d_m> &B) {

};

std::vector<double> *double_2d_m::mult(const std::vector<double_2d_m> &B) {

};


// SETTERS
// Allowing you to modify values in a matrix, they edit the transpose simultaneously.

void uint16_t_2d_m::set(const int &pos, uint16_t val) {
    matrix[pos] = val;
    
    int pos_row = pos / columns;
    int pos_col = pos - (pos_row * columns);
    transpose[pos_col * rows + pos_row] = val;
};

void uint32_t_2d_m::set(const int &pos, uint32_t val) {
    matrix[pos] = val;
    
    int pos_row = pos / columns;
    int pos_col = pos - (pos_row * columns);
    transpose[pos_col * rows + pos_row] = val;
};

void uint64_t_2d_m::set(const int &pos, uint64_t val) {
    matrix[pos] = val;
    
    int pos_row = pos / columns;
    int pos_col = pos - (pos_row * columns);
    transpose[pos_col * rows + pos_row] = val;
};

void float_2d_m::set(const int &pos, float val) {
    matrix[pos] = val;
    
    int pos_row = pos / columns;
    int pos_col = pos - (pos_row * columns);
    transpose[pos_col * rows + pos_row] = val;
};

void double_2d_m::set(const int &pos, double val) {
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
