#include <immintrin.h> // AVX 头文件

int main()
{
    _Alignas(32) float a[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    _Alignas(32) float b[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    _Alignas(32) float result[8];

    // 加载到 256 位寄存器（8 个 float）
    __m256 va = _mm256_load_ps(a);
    __m256 vb = _mm256_load_ps(b);

    // 一条指令：8 个 float 同时相加！
    __m256 vres = _mm256_add_ps(va, vb);

    // 存回内存
    _mm256_store_ps(result, vres);
}

// gcc -mavx avx_exp.c -o avx_exp