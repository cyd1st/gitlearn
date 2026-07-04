/**
# 编译两个版本并测试
gcc -O2 -no-pie test.c -o test_nopie
gcc -O2 -fPIE -pie test.c -o test_pie

测试PIE是否有性能差别，理论上是有的，但应该很小。
*/
#include <stdio.h>
#include <time.h>

int global = 42;

int main()
{
    clock_t start = clock();
    long long sum = 0;

    for (int i = 0; i < 2000000000; i++) {
        sum += global; // 频繁访问全局变量
    }

    clock_t end = clock();
    printf("Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("Sum: %lld\n", sum); // 防止优化
    return 0;
}