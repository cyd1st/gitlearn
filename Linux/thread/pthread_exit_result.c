#include <stdio.h>
#include <stdlib.h> // 为了使用 malloc 和 free
#include <pthread.h>

void *computeSum(void *arg);

int main() {
    int n = 10; // 计算前 n 个自然数的和
    pthread_t computeSum_id;
    pthread_create(&computeSum_id, NULL, computeSum, (void *)&n);

    // 等待线程完成
    void *result;
    pthread_join(computeSum_id, &result);

    // 获取计算结果
    long long sum = *(long long *)result;
    printf("前 %d 个自然数的和：%lld\n", n, sum);

    // 释放内存
    free(result);

    return 0;
}

void *computeSum(void *arg) {
    int n = *(int *)arg;
    long long *result = (long long *)malloc(sizeof(long long));
    *result = 0;

    for (int i = 1; i <= n; ++i) {
        *result += i;
    }

    // 返回计算结果
    pthread_exit(result);
}
