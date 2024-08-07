/**
    比较单线程与多线程累加计算的耗时。
 */
#include <bits/time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <threads.h>
#include <time.h>

void *thread_accumulte(void *arg);
int range[] = {1, 1000000};

int calculate_by_threads(int s, int e)
{
    struct timespec start, end;
    double elapsed_time;
    clock_gettime(CLOCK_MONOTONIC, &start);

    pthread_t t1, t2;
    int range1[] = {s, e / 2};
    int range2[] = {e / 2 + 1, e};

    pthread_create(&t1, NULL, thread_accumulte, range1);
    pthread_create(&t2, NULL, thread_accumulte, range2);

    long long *sum1 = NULL, *sum2 = NULL;
    pthread_join(t1, (void **)&sum1);
    pthread_join(t2, (void **)&sum2);

    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("sum by multi threads: %lld, takes %fms\n", *(long long *)sum1 + *(long long *)sum2, elapsed_time * 1000);
    free(sum1); // 别忘了free
    free(sum2);
    return 0;
}

void *thread_accumulte(void *arg)
{
    int start = ((int *)arg)[0];
    int end = ((int *)arg)[1];
    long long sum = 0;

    while (start <= end) {
        sum += start;
        start++;
    }
    
    long long *res = (long long *)malloc(sizeof(long long));
    *res = sum;
    pthread_exit(res);
}

int calculate_by_main(int s, int e)
{
    struct timespec start_time, end_time;
    double elapsed_time;

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    long long sum = 0;
    int start = s;
    int end = e;

    while (start <= end) {
        sum += start;
        start++;
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec -  start_time.tv_nsec) / 1000000000.0;
    printf("sum by single thread: %lld, takes %fms\n", sum, elapsed_time * 1000);
    return 0;
}

int testcase(int s, int e)
{
    printf("accumulate from %d to %d\n", s, e);
    calculate_by_main(s, e);
    calculate_by_threads(s, e);
    return 0;
}

int main()
{
    testcase(1, 1000);
    testcase(1, 10000);
    testcase(1, 100000);
    testcase(1, 1000000);
    testcase(1, 10000000);
    testcase(1, 100000000);
    testcase(1, 1000000000);

    return 0;
}