#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig)
{
    if (sig == SIGALRM) {
        puts("Time out.");
    }
    /* alram 函数将会产生一个 SIGALRM 信号，
     * 结合 main 的 SIGALRM 注册语句，这个信号会
     * 递归的触发下去。
     */
    alarm(2);
}

void keycontrol(int sig)
{
    if (sig == SIGINT) {
        puts("CTRL+C pressed.");
    }
}

int main()
{
    signal(SIGALRM, timeout);
    signal(SIGINT, keycontrol);
    alarm(2);

    /* 信号会唤醒 sleep 的进程，所以执行程序快速按几次ctrl+c，就可以迅速结束程序 */
    for (int i = 0; i < 3; i++) {
        puts("wait...");
        sleep(100);
    }
    return 0;
}