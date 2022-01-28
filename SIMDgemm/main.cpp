#include <iostream>
#include <vector>
#include <string>
#include <cassert>

#include <x86intrin.h>
#include "matrix.h"

int main()
{
    int ROWS = 6;
    int COLUMNS = 8;
    uint32_t_2d_m test(ROWS, COLUMNS);
    assert(test.matrix.size() == ROWS*COLUMNS);

    for (int i = 1; i <= ROWS*COLUMNS; i++) {
        std::cout << i-1 << ' ';
        test.matrix[i-1] = i-1;
        if (((float)i / COLUMNS)-(i/COLUMNS) == 0)
            std::cout << std::endl;
    }

    std::cout << "\n" << std::endl;

    for (int i = 1; i <= ROWS*COLUMNS; i++) {
        std::cout << test.matrix[i - 1] << ' ';
        if (((float)i / COLUMNS) - (i / COLUMNS) == 0)
            std::cout << std::endl;
    }

    test.transpose();
    std::cout << "\n" << std::endl;

    for (int i = 1; i <= ROWS*COLUMNS; i++) {
        std::cout << test.matrix[i - 1] << ' ';
        if (((float)i / ROWS) - (i / ROWS) == 0)
            std::cout << std::endl;
    }
}