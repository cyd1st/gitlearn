#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

static int glob = 0;
static pthread_mutex_t mux;

static void *threadFunc(void *arg);

int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    int loops, s;
    pthread_mutexattr_t muxAttr;

    pthread_mutexattr_init(&muxAttr);
    // 设置 PTHREAD_MUTEX_ERRORCHECK 属性的互斥锁。
    // 该属性一般用于debug阶段检测，同一线程，重复获取同一 mutex 的情况
    pthread_mutexattr_settype(&muxAttr, PTHREAD_MUTEX_ERRORCHECK);
    pthread_mutex_init(&mux, &muxAttr);

    loops = argc > 1 ? atoi(argv[1]) : 10000000;

    pthread_create(&t1, NULL, threadFunc, &loops);
    pthread_create(&t2, NULL, threadFunc, &loops);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("glob = %d\n", glob);
    
    pthread_mutex_destroy(&mux);
    return 0;
}

static void *threadFunc(void *arg)
{
    int loops = *((int *)arg);
    int loc, ret;

    pthread_mutex_lock(&mux); // 重复的lock触发 PTHREAD_MUTEX_ERRORCHECK 属性

    for(int j = 0; j < loops; j++) {
        ret = pthread_mutex_lock(&mux);
        if (ret != 0) {
            // 这一行将会打印
            printf("%d\t%s(%d).\n", __LINE__, strerror(ret), ret);
            // 注意返回前先解锁，否则会死锁。
            pthread_mutex_unlock(&mux);
            return NULL;
        }

        loc = glob;
        loc++;
        glob = loc;

        ret = pthread_mutex_unlock(&mux);
        if (ret != 0) {
            printf("pthread_mutex_unlock ERROR.\n");
        }
    }

    pthread_mutex_unlock(&mux);

    return NULL;
}