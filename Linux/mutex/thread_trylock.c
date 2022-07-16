#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <errno.h>
#include <unistd.h>

static int *pthreadFunc(void *arg);
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main()
{
    pthread_t t1;
    
    pthread_mutex_lock(&mutex);
    pthread_create(&t1, NULL, (void *)pthreadFunc, NULL);
    sleep(1);
    pthread_mutex_unlock(&mutex);

    return 0;
}

static int *pthreadFunc(void *arg)
{
    int ret;

    ret = pthread_mutex_trylock(&mutex);
    assert(ret != EBUSY);

    return NULL;
}
