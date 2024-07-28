#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h> // sleep

void *fun(void *arg);

int main() {

    pthread_t pid;
    pthread_create(&pid, NULL, fun, NULL);

    // 取消线程
    int ret1 = pthread_cancel(pid);
    printf("ret1 = %d\n", ret1);
    // 取消一个不存在的线程
    int ret2 = pthread_cancel(pid - 1);
    if (ret2 == ESRCH) {
        printf("ret2 = ESRCH\n");
    } else {
        printf("ret2 = %d\n", ret2);
    }
    

    // 等待线程完成
    pthread_join(pid, NULL);

    return 0;
}

void *fun(void *arg) {
    while(1) {
        sleep(200); // 改为 2 就报错？
        // 添加取消点
        pthread_testcancel();
    }
}
