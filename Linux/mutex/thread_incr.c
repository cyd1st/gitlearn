#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

static int glob = 0;

static void *threadFunc(void *arg)
{
    int loops = *((int *)arg);
    int loc, j;

    for(j = 0; j < loops; j++) {
        loc = glob;
        loc++;
        glob = loc;
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
