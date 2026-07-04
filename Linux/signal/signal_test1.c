/*
 * @Descripttion: 使用signal()函数处理信号
 * @Author: cyd
 * @Date: 2021-08-02 14:38:11
 * @LastEditTime: 2021-08-02 15:34:45
 */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sigrg(int signum)
{
    switch (signum) {
    case SIGHUP:
        // 注意printf末尾需要\n否则不会刷新缓冲区
        printf("Get a signal: SIGHUP\n");
        break;
    case SIGINT:
        printf("Get a signal: SIGINT\n");
        break;
    case SIGQUIT:
        printf("Get a signal: SIGQUIT\n");
        break;
    default:
        printf("unknown signal\n");
        break;
    }

    return;
}

int main()
{
    signal(SIGHUP, sigrg);
    // Ctrl + C
    signal(SIGINT, sigrg);
    signal(SIGQUIT, sigrg);

    for (;;) {
        sleep(1);
    }
}
