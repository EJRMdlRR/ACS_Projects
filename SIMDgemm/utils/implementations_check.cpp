#include <iostream>

int main()
{
    __builtin_cpu_init();

    std::cout << "sse: " << __builtin_cpu_supports("sse") << std::endl;
    std::cout << "sse2: " << __builtin_cpu_supports("sse2") << std::endl;
    std::cout << "sse3: " << __builtin_cpu_supports("sse3") << std::endl;
    std::cout << "ssse3: " << __builtin_cpu_supports("ssse3") << std::endl;
    std::cout << "sse4: " << __builtin_cpu_supports("sse4.1") << std::endl;
    std::cout << "sse4: " << __builtin_cpu_supports("sse4.2") << std::endl;
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
    std::cout << "avx512vl: " << __builtin_cpu_supports("avx512vl") << std::endl;
    std::cout << "avx512bw: " << __builtin_cpu_supports("avx512bw") << std::endl;
    std::cout << "avx512dq: " << __builtin_cpu_supports("avx512dq") << std::endl;
    std::cout << "avx512cd: " << __builtin_cpu_supports("avx512cd") << std::endl;
    std::cout << "avx512er: " << __builtin_cpu_supports("avx512er") << std::endl;
    std::cout << "avx512pf: " << __builtin_cpu_supports("avx512pf") << std::endl;
    std::cout << "avx512vbmi: " << __builtin_cpu_supports("avx512vbmi") << std::endl;
    std::cout << "avx512ifma: " << __builtin_cpu_supports("avx512ifma") << std::endl;
    std::cout << "avx5124vnniw: " << __builtin_cpu_supports("avx5124vnniw") << std::endl;
    std::cout << "avx5124fmaps: " << __builtin_cpu_supports("avx5124fmaps") << std::endl;
    std::cout << "avx512vpopcntdq: " << __builtin_cpu_supports("avx512vpopcntdq") << std::endl;
    std::cout << "avx512vbmi2: " << __builtin_cpu_supports("avx512vbmi2") << std::endl;
    std::cout << "gfni: " << __builtin_cpu_supports("gfni") << std::endl;
    std::cout << "vpclmulqdq: " << __builtin_cpu_supports("vpclmulqdq") << std::endl;
    std::cout << "avx512vnni: " << __builtin_cpu_supports("avx512vnni") << std::endl;
}