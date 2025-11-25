#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>
#include <math.h>

#define ARRAY_SIZE 1000000
#define ITERATIONS 100

// 普通C语言实现复杂计算: result[i] = a[i]*b[i] + a[i]^0.5 + b[i]^2
void complex_calc_normal(float* a, float* b, float* result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = a[i] * b[i] + sqrtf(a[i]) + b[i] * b[i];
    }
}

// 使用AVX指令集实现复杂计算
void complex_calc_avx(float* a, float* b, float* result, int size) {
    int i = 0;
    
    // 处理能被8整除的部分
    for (; i <= size - 8; i += 8) {
        __m256 va = _mm256_load_ps(&a[i]);
        __m256 vb = _mm256_load_ps(&b[i]);
        
        // 计算 a*b
        __m256 vmul = _mm256_mul_ps(va, vb);
        
        // 计算 sqrt(a)
        // 注意：这里简化处理，实际SIMD的sqrt计算比标量版本更复杂
        __m256 vsqrt = _mm256_sqrt_ps(va);
        
        // 计算 b*b
        __m256 vb2 = _mm256_mul_ps(vb, vb);
        
        // 计算最终结果: a*b + sqrt(a) + b*b
        __m256 vtemp = _mm256_add_ps(vmul, vsqrt);
        __m256 vres = _mm256_add_ps(vtemp, vb2);
        
        _mm256_store_ps(&result[i], vres);
    }
    
    // 处理剩余不足8个元素的部分
    for (; i < size; i++) {
        result[i] = a[i] * b[i] + sqrtf(a[i]) + b[i] * b[i];
    }
}

// 更复杂的数学运算示例：多项式计算
void polynomial_calc_normal(float* input, float* output, int size) {
    for (int i = 0; i < size; i++) {
        // 计算 3*x^4 + 2*x^3 + 5*x^2 + x + 7
        float x = input[i];
        float x2 = x * x;
        float x3 = x2 * x;
        float x4 = x3 * x;
        output[i] = 3*x4 + 2*x3 + 5*x2 + x + 7;
    }
}

void polynomial_calc_avx(float* input, float* output, int size) {
    const __m256 c3 = _mm256_set1_ps(3.0f);
    const __m256 c2 = _mm256_set1_ps(2.0f);
    const __m256 c5 = _mm256_set1_ps(5.0f);
    const __m256 c1 = _mm256_set1_ps(1.0f);
    const __m256 c7 = _mm256_set1_ps(7.0f);
    
    int i = 0;
    for (; i <= size - 8; i += 8) {
        __m256 x = _mm256_load_ps(&input[i]);
        
        // 计算各次幂
        __m256 x2 = _mm256_mul_ps(x, x);
        __m256 x3 = _mm256_mul_ps(x2, x);
        __m256 x4 = _mm256_mul_ps(x3, x);
        
        // 计算各项
        __m256 t1 = _mm256_mul_ps(c3, x4);
        __m256 t2 = _mm256_mul_ps(c2, x3);
        __m256 t3 = _mm256_mul_ps(c5, x2);
        __m256 t4 = _mm256_mul_ps(c1, x);
        
        // 相加得到最终结果
        __m256 temp1 = _mm256_add_ps(t1, t2);
        __m256 temp2 = _mm256_add_ps(temp1, t3);
        __m256 temp3 = _mm256_add_ps(temp2, t4);
        __m256 result = _mm256_add_ps(temp3, c7);
        
        _mm256_store_ps(&output[i], result);
    }
    
    // 处理剩余元素
    for (; i < size; i++) {
        float x = input[i];
        float x2 = x * x;
        float x3 = x2 * x;
        float x4 = x3 * x;
        output[i] = 3*x4 + 2*x3 + 5*x2 + x + 7;
    }
}

// 初始化数组
void init_arrays(float* a, float* b, int size) {
    for (int i = 0; i < size; i++) {
        a[i] = (float)(rand() % 1000) / 10.0f + 1.0f; // 避免负数和0，以便开方
        b[i] = (float)(rand() % 1000) / 10.0f;
    }
}

// 计算时间差（以秒为单位）
double time_diff(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
}

int main() {
    // 分配内存对齐的数组
    float* a = (float*)_mm_malloc(ARRAY_SIZE * sizeof(float), 32);
    float* b = (float*)_mm_malloc(ARRAY_SIZE * sizeof(float), 32);
    float* result_normal1 = (float*)_mm_malloc(ARRAY_SIZE * sizeof(float), 32);
    float* result_avx1 = (float*)_mm_malloc(ARRAY_SIZE * sizeof(float), 32);
    float* result_normal2 = (float*)_mm_malloc(ARRAY_SIZE * sizeof(float), 32);
    float* result_avx2 = (float*)_mm_malloc(ARRAY_SIZE * sizeof(float), 32);
    
    // 初始化随机数种子
    srand(time(NULL));
    
    // 初始化输入数组
    init_arrays(a, b, ARRAY_SIZE);
    
    printf("复杂运算性能比较\n");
    printf("==================\n");
    printf("数组大小: %d\n", ARRAY_SIZE);
    printf("迭代次数: %d\n\n", ITERATIONS);
    
    // 测试复杂计算的性能
    struct timespec start_normal, end_normal, start_avx, end_avx;
    
    // 测试普通C实现的性能
    clock_gettime(CLOCK_MONOTONIC, &start_normal);
    for (int i = 0; i < ITERATIONS; i++) {
        complex_calc_normal(a, b, result_normal1, ARRAY_SIZE);
    }
    clock_gettime(CLOCK_MONOTONIC, &end_normal);
    double normal_time1 = time_diff(start_normal, end_normal);
    
    // 测试AVX实现的性能
    clock_gettime(CLOCK_MONOTONIC, &start_avx);
    for (int i = 0; i < ITERATIONS; i++) {
        complex_calc_avx(a, b, result_avx1, ARRAY_SIZE);
    }
    clock_gettime(CLOCK_MONOTONIC, &end_avx);
    double avx_time1 = time_diff(start_avx, end_avx);
    
    printf("复杂运算 (a*b + sqrt(a) + b^2):\n");
    printf("普通C实现耗时: %.6f 秒\n", normal_time1);
    printf("AVX实现耗时: %.6f 秒\n", avx_time1);
    printf("性能提升: %.2fx\n\n", normal_time1 / avx_time1);
    
    // 测试多项式计算的性能
    clock_gettime(CLOCK_MONOTONIC, &start_normal);
    for (int i = 0; i < ITERATIONS; i++) {
        polynomial_calc_normal(a, result_normal2, ARRAY_SIZE);
    }
    clock_gettime(CLOCK_MONOTONIC, &end_normal);
    double normal_time2 = time_diff(start_normal, end_normal);
    
    clock_gettime(CLOCK_MONOTONIC, &start_avx);
    for (int i = 0; i < ITERATIONS; i++) {
        polynomial_calc_avx(a, result_avx2, ARRAY_SIZE);
    }
    clock_gettime(CLOCK_MONOTONIC, &end_avx);
    double avx_time2 = time_diff(start_avx, end_avx);
    
    printf("多项式运算 (3*x^4 + 2*x^3 + 5*x^2 + x + 7):\n");
    printf("普通C实现耗时: %.6f 秒\n", normal_time2);
    printf("AVX实现耗时: %.6f 秒\n", avx_time2);
    printf("性能提升: %.2fx\n\n", normal_time2 / avx_time2);
    
    // 验证结果一致性（只检查前10个元素）
    printf("结果验证（前10个元素）:\n");
    printf("复杂运算验证:\n");
    printf("Index\tNormal\tAVX\tDifference\n");
    for (int i = 0; i < 10; i++) {
        float diff = result_normal1[i] - result_avx1[i];
        printf("%d\t%.3f\t%.3f\t%.6f\n", i, result_normal1[i], result_avx1[i], diff);
    }
    
    printf("\n多项式运算验证:\n");
    printf("Index\tNormal\tAVX\tDifference\n");
    for (int i = 0; i < 10; i++) {
        float diff = result_normal2[i] - result_avx2[i];
        printf("%d\t%.3f\t%.3f\t%.6f\n", i, result_normal2[i], result_avx2[i], diff);
    }
    
    // 释放内存
    _mm_free(a);
    _mm_free(b);
    _mm_free(result_normal1);
    _mm_free(result_avx1);
    _mm_free(result_normal2);
    _mm_free(result_avx2);
    
    return 0;
}