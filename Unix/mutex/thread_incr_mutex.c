#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

static int glob = 0;
static pthread_mutex_t mux = PTHREAD_MUTEX_INITIALIZER;

static void *threadFunc(void *arg)
{
    int loops = *((int *)arg);
    int loc, j, ret;

    for(j = 0; j < loops; j++) {
	ret = pthread_mutex_lock(&mux);
	if (ret != 0) {
	    printf("pthread_mutex_lock ERROR.\n");
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

    loops = argc > 1 ? atoi(argv[1]) : 10000000;

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

    printf("glob = %d\n", glob);

    return 0;
}
