#include <iostream>

int main()
{
    __builtin_cpu_init();
    std::cout << "sse: " << __builtin_cpu_supports("sse") << std::endl;
    std::cout << "sse2: " << __builtin_cpu_supports("sse2") << std::endl;
    std::cout << "sse3: " << __builtin_cpu_supports("sse3") << std::endl;
    std::cout << "ssse3: " << __builtin_cpu_supports("ssse3") << std::endl;
    std::cout << "sse4.1: " << __builtin_cpu_supports("sse4.1") << std::endl;
    std::cout << "sse4.2: " << __builtin_cpu_supports("sse4.2") << std::endl;
    std::cout << "avx: " << __builtin_cpu_supports("avx") << std::endl;
    std::cout << "avx2: " << __builtin_cpu_supports("avx2") << std::endl;
    std::cout << "sse4a: " << __builtin_cpu_supports("sse4a") << std::endl;
    std::cout << "fma4: " << __builtin_cpu_supports("fma4") << std::endl;
    std::cout << "xop: " << __builtin_cpu_supports("xop") << std::endl;
    std::cout << "fma: " << __builtin_cpu_supports("fma") << std::endl;
    std::cout << "avx512f: " << __builtin_cpu_supports("avx512f") << std::endl;
    std::cout << "bmi: " << __builtin_cpu_supports("bmi") << std::endl;
    std::cout << "bmi2: " << __builtin_cpu_supports("bmi2") << std::endl;
    std::cout << "aes: " << __builtin_cpu_supports("aes") << std::endl;
    std::cout << "pclmul: " << __builtin_cpu_supports("pclmul") << std::endl;
}