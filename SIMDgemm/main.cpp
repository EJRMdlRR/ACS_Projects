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
    assert(test.get_m().size() == ROWS*COLUMNS);

    for (int i = 1; i <= ROWS*COLUMNS; i++) {
        std::cout << i-1 << ' ';
        test.set(i-1, i-1);
        if (((float)i / COLUMNS)-(i/COLUMNS) == 0)
            std::cout << std::endl;
    }

    std::cout << "\n" << std::endl;

    for (int i = 1; i <= ROWS*COLUMNS; i++) {
        std::cout << test.get(i - 1) << ' ';
        if (((float)i / COLUMNS) - (i / COLUMNS) == 0)
            std::cout << std::endl;
    }

    std::cout << "\n" << std::endl;

    std::vector<uint32_t> test_transpose = test.get_t();
    for (int i = 1; i <= ROWS*COLUMNS; i++) {
        std::cout << test_transpose[i - 1] << ' ';
        if (((float)i / ROWS) - (i / ROWS) == 0)
            std::cout << std::endl;
    }
}