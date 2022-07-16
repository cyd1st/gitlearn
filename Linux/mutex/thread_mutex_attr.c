#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

static int glob = 0;
static pthread_mutex_t mux;

static void *threadFunc(void *arg)
{
    int loops = *((int *)arg);
    int loc, j, ret;

    for(j = 0; j < loops; j++) {
	ret = pthread_mutex_lock(&mux);
	if (ret != 0) {
	    printf("pthread_mutex_lock ERROR.\n");
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

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    int loops, s;
    pthread_mutexattr_t muxAttr;

    s = pthread_mutexattr_init(&muxAttr);
    if (s != 0) {
        printf("pthread_mutexattr_init faild.\n");
    }
    s = pthread_mutexattr_settype(&muxAttr, PTHREAD_MUTEX_ERRORCHECK);
    if (s != 0) {
        printf("pthread_mutexattr_settype failed.\n");
    }
    s = pthread_mutex_init(&mux, &muxAttr);
    if (s != 0) {
        printf("pthread_mutex_init failed.\n");
    }

    loops = argc > 1 ? atoi(argv[1]) : 10000000;

    pthread_mutex_lock(&mux);
    s = pthread_create(&t1, NULL, threadFunc, &loops);
    if (s != 0) {
        printf("pthread_create t1 failed.\n");
    }

    s = pthread_create(&t2, NULL, threadFunc, &loops);
    if (s != 0) { 
        printf("pthread_create t2 failed.\n");
    }
    
    s = pthread_join(t1, NULL);
    if (s != 0) {
        printf("pthread_join t1 failed.\n");
    }
    s = pthread_join(t2, NULL);
    if (s != 0) {
        printf("pthread_join t2 failed.\n");
    }
    pthread_mutex_unlock(&mux);

    printf("glob = %d\n", glob);

    return 0;
}
