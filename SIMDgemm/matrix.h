#include <cstdint>
#include <vector>

class uint16_t_2d_m
{
public:
    uint16_t_2d_m(int r, int c) : rows(r), columns(c), matrix(std::vector<uint16_t>(r * c)), transpose(std::vector<uint16_t>(r * c)) {}

    std::vector<uint16_t> mult(uint16_t_2d_m &B);

    void set(const int &pos, uint16_t val);
    uint16_t get(const int &pos) { return matrix[pos]; }
    const std::vector<uint16_t> &get_m() { return matrix; }
    const std::vector<uint16_t> &get_t() { return transpose; }

    std::pair<int, int> shape() { return std::pair<int, int>(rows, columns); }
    const int get_rows() { return rows; }
    const int get_columns() { return columns; }

private:
    uint32_t rows;
    uint32_t columns;
    std::vector<uint16_t> matrix;
    std::vector<uint16_t> transpose;

    void do_transpose();
};

class uint32_t_2d_m
{
public:
    uint32_t_2d_m(int r, int c) : rows(r), columns(c), matrix(std::vector<uint32_t>(r * c)), transpose(std::vector<uint32_t>(r * c)) {}

    std::vector<uint32_t> mult(uint32_t_2d_m &B);

    void set(const int &pos, uint32_t val);
    uint32_t get(const int &pos) { return matrix[pos]; }
    const std::vector<uint32_t> &get_m() { return matrix; }
    const std::vector<uint32_t> &get_t() { return transpose; }

    std::pair<int, int> shape() { return std::pair<int, int>(rows, columns); }
    const int get_rows() { return rows; }
    const int get_columns() { return columns; }

private:
    uint32_t rows;
    uint32_t columns;
    std::vector<uint32_t> matrix;
    std::vector<uint32_t> transpose;

    void do_transpose();
};

class uint64_t_2d_m
{
public:
    uint64_t_2d_m(int r, int c) : rows(r), columns(c), matrix(std::vector<uint64_t>(r * c)), transpose(std::vector<uint64_t>(r * c)) {}

    std::vector<uint64_t> mult(uint64_t_2d_m &B);

    void set(const int &pos, uint64_t val);
    uint64_t get(const int &pos) { return matrix[pos]; }
    const std::vector<uint64_t> &get_m() { return matrix; }
    const std::vector<uint64_t> &get_t() { return transpose; }

    std::pair<int, int> shape() { return std::pair<int, int>(rows, columns); }
    const int get_rows() { return rows; }
    const int get_columns() { return columns; }

private:
    uint32_t rows;
    uint32_t columns;
    std::vector<uint64_t> matrix;
    std::vector<uint64_t> transpose;

    void do_transpose();
};

class float_2d_m
{
public:
    float_2d_m(int r, int c) : rows(r), columns(c), matrix(std::vector<float>(r * c)), transpose(std::vector<float>(r * c)) {}

    std::vector<float> mult(float_2d_m &B);

    void set(const int &pos, float val);
    float get(const int &pos) { return matrix[pos]; }
    const std::vector<float> &get_m() { return matrix; }
    const std::vector<float> &get_t() { return transpose; }

    std::pair<int, int> shape() { return std::pair<int, int>(rows, columns); }
    const int get_rows() { return rows; }
    const int get_columns() { return columns; }

private:
    uint32_t rows;
    uint32_t columns;
    std::vector<float> matrix;
    std::vector<float> transpose;

    void do_transpose();
};

class double_2d_m
{
public:
    double_2d_m(int r, int c) : rows(r), columns(c), matrix(std::vector<double>(r * c)), transpose(std::vector<double>(r * c)) {}

    std::vector<double> mult(double_2d_m &B);

    void set(const int &pos, double val);
    double get(const int &pos) { return matrix[pos]; }
    const std::vector<double> &get_m() { return matrix; }
    const std::vector<double> &get_t() { return transpose; }

    std::pair<int, int> shape() { return std::pair<int, int>(rows, columns); }
    const int get_rows() { return rows; }
    const int get_columns() { return columns; }

private:
    uint32_t rows;
    uint32_t columns;
    std::vector<double> matrix;
    std::vector<double> transpose;

    void do_transpose();
};
