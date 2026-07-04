#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>

#define ARRAY_SIZE 1000000
#define ITERATIONS 1000

// 普通C语言实现向量加法
void add_arrays_normal(float* a, float* b, float* result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = a[i] + b[i];
    }
}

// 使用AVX指令集实现向量加法
void add_arrays_avx(float* a, float* b, float* result, int size) {
    int i = 0;
    
    // 处理能被8整除的部分
    for (; i <= size - 8; i += 8) {
        __m256 va = _mm256_load_ps(&a[i]);
        __m256 vb = _mm256_load_ps(&b[i]);
        __m256 vres = _mm256_add_ps(va, vb);
        _mm256_store_ps(&result[i], vres);
    }
    
    // 处理剩余不足8个元素的部分
    for (; i < size; i++) {
        result[i] = a[i] + b[i];
    }
}

// 初始化数组
void init_arrays(float* a, float* b, int size) {
    for (int i = 0; i < size; i++) {
        a[i] = (float)(rand() % 1000) / 100.0f;
        b[i] = (float)(rand() % 1000) / 100.0f;
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
    float* result_normal = (float*)_mm_malloc(ARRAY_SIZE * sizeof(float), 32);
    float* result_avx = (float*)_mm_malloc(ARRAY_SIZE * sizeof(float), 32);
    
    // 初始化随机数种子
    srand(time(NULL));
    
    // 初始化输入数组
    init_arrays(a, b, ARRAY_SIZE);
    
    // 测试普通C实现的性能
    struct timespec start_normal, end_normal;
    clock_gettime(CLOCK_MONOTONIC, &start_normal);
    
    for (int i = 0; i < ITERATIONS; i++) {
        add_arrays_normal(a, b, result_normal, ARRAY_SIZE);
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end_normal);
    double normal_time = time_diff(start_normal, end_normal);
    
    // 测试AVX实现的性能
    struct timespec start_avx, end_avx;
    clock_gettime(CLOCK_MONOTONIC, &start_avx);
    
    for (int i = 0; i < ITERATIONS; i++) {
        add_arrays_avx(a, b, result_avx, ARRAY_SIZE);
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end_avx);
    double avx_time = time_diff(start_avx, end_avx);
    
    // 输出结果
    printf("数组大小: %d\n", ARRAY_SIZE);
    printf("迭代次数: %d\n", ITERATIONS);
    printf("普通C实现耗时: %.6f 秒\n", normal_time);
    printf("AVX实现耗时: %.6f 秒\n", avx_time);
    printf("性能提升: %.2fx\n", normal_time / avx_time);
    
    // 验证结果是否一致（只检查前10个元素）
    printf("\n结果验证（前10个元素）:\n");
    printf("Index\tNormal\tAVX\tDifference\n");
    for (int i = 0; i < 10; i++) {
        float diff = result_normal[i] - result_avx[i];
        printf("%d\t%.3f\t%.3f\t%.6f\n", i, result_normal[i], result_avx[i], diff);
    }
    
    // 释放内存
    _mm_free(a);
    _mm_free(b);
    _mm_free(result_normal);
    _mm_free(result_avx);
    
    return 0;
}