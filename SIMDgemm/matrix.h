#include <cstdint>
#include <vector>

class uint16_t_2d_m {
    public:
    int rows;
    int columns;

    void transpose();
    std::vector<uint16_t> matrix;
};

class uint32_t_2d_m {
    public :
        uint32_t_2d_m(int rows, int columns);

        void transpose();

        int rows;
        int columns;
        std::vector<uint32_t> matrix;
};

class uint64_t_2d_m {
    public:
    int rows;
    int columns;

    void transpose();
    std::vector<uint64_t> matrix;
};

class float_2d_m {
    public:
    int rows;
    int columns;

    void transpose();
    std::vector<float> matrix;
};

class double_2d_m {
    public:
    int rows;
    int columns;

    void transpose();
    std::vector<double> matrix;
};
