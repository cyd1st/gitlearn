#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void Quit(int sig)
{
    if (sig == SIGINT) {
        puts("是否真的要退出？输入Y确认");
        char buf[10];
        fgets(buf, 9, stdin);
        if (!strcmp(buf, "y\n") || !strcmp(buf, "Y\n")) {
            exit(1);
        }
    }
}
int main()
{
    struct sigaction act;
    act.sa_handler = Quit;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);

    while (1) {
        sleep(100);
    }

    return 0;
}