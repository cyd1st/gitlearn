/**
    临界区没有保护的情况。
 */
#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define THREAD_NUM 100

long long sum = 0;

void * thread_inc(void *arg);
void * thread_dec(void *arg);

int main()
{
    pthread_t threads[THREAD_NUM];

    // 创建线程
    for (int i = 0; i < THREAD_NUM; i++) {
        if (i % 2) {
            pthread_create(&threads[i], NULL, thread_inc, NULL);
        } else {
            pthread_create(&threads[i], NULL, thread_dec, NULL);
        }
    }

    // 合并线程
    for (int i = 0; i < THREAD_NUM; i++) {
        pthread_join(threads[i], NULL);
    }

    // 打印结构
    printf("sum : %lld\n", sum);
    return 0;
}

void *thread_inc(void *arg)
{
    for (int i = 0; i < 50000000; i++) {
        sum += i;
    }
    return NULL;
}

void *thread_dec(void *arg)
{
    for (int i = 0; i < 50000000; i++) {
        sum -= i;
    }
    return NULL;
}