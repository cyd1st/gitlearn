#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// 清理函数原型
void cleanup_function1(void *arg);
void cleanup_function2(void *arg);

// 线程函数
void *myThreadFunction(void *arg);

int main() {
    pthread_t thread_id;

    // 创建线程
    if (pthread_create(&thread_id, NULL, myThreadFunction, NULL) != 0) {
        fprintf(stderr, "Failed to create thread\n");
        return 1;
    }

    // 触发 pthread_testcancel(可以试试注释这段代码与不注释的区别)
    sleep(3);
    pthread_cancel(thread_id);

    // 等待线程完成
    if (pthread_join(thread_id, NULL) != 0) {
        fprintf(stderr, "Failed to join thread\n");
        return 1;
    }

    printf("Main thread exiting.\n");

    return 0;
}

// 线程函数
void *myThreadFunction(void *arg) {
    int i;

    // 注册清理函数
    pthread_cleanup_push(cleanup_function1, (void *)1);
    pthread_cleanup_push(cleanup_function2, (void *)2);

    // 线程执行的代码
    for (i = 0; i < 10; i++) {
        printf("Thread is running...\n");
        sleep(1);
    }

    // 取消最上面的清理函数
    pthread_cleanup_pop(1); // 调用cleanup_function1
    printf("clean up pop 1\n");

    // 线程可以在此处被取消
    pthread_testcancel();

    // 取消第二个清理函数
    pthread_cleanup_pop(1); // 调用cleanup_function2
    printf("clean up pop 2\n");

    // 线程正常退出
    pthread_exit(NULL);
}

// 清理函数 1
void cleanup_function1(void *arg) {
    int id = (int)arg;
    printf("Cleanup function 1 called with arg %d\n", id);
}

// 清理函数 2
void cleanup_function2(void *arg) {
    int id = (int)arg;
    printf("Cleanup function 2 called with arg %d\n", id);
}