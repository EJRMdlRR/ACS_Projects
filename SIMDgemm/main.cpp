#include <iostream>
#include <vector>
#include <string>
#include <cassert>

#include <x86intrin.h>
#include "matrix.h"

int main()
{
    uint32_t ROWS = 8;
    uint32_t COLUMNS = 17;
    uint16_t_2d_m test(ROWS, COLUMNS);
    assert(test.get_m().size() == ROWS * COLUMNS);

    for (uint32_t i = 1; i <= ROWS * COLUMNS; i++)
        test.set(i - 1, i - 1);

    for (uint32_t i = 1; i <= ROWS * COLUMNS; i++)
    {
        std::cout << test.get(i - 1) << ' ';
        if (((float)i / COLUMNS) - (i / COLUMNS) == 0)
            std::cout << std::endl;
    }

    std::cout << "\n"
              << std::endl;

    ROWS = 17;
    COLUMNS = 4;
    uint16_t_2d_m B(ROWS, COLUMNS);
    assert(B.get_m().size() == ROWS * COLUMNS);

    for (uint32_t i = 1; i <= ROWS * COLUMNS; i++)
        B.set(i - 1, i - 1);

    for (uint32_t i = 1; i <= ROWS * COLUMNS; i++)
    {
        std::cout << B.get(i - 1) << ' ';
        if (((float)i / COLUMNS) - (i / COLUMNS) == 0)
            std::cout << std::endl;
    }

    std::cout << "\n"
              << std::endl;

    std::vector<uint16_t> result = test.mult(B);
    for (uint32_t i = 1; i <= result.size(); i++)
    {
        std::cout << result[i - 1] << ' ';
        if (((float)i / 4) - (i / 4) == 0)
            std::cout << std::endl;
    }
}