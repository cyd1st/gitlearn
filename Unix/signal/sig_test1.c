/*
 * @Descripttion: 
 * @Author: cyd
 * @Date: 2021-08-02 14:38:11
 * @LastEditTime: 2021-08-02 15:34:45
 */
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void sigrg(int signum)
{
    switch (signum)
    {
        case SIGHUP:
            printf("Get a signal: SIGHUP");
            break;
        case SIGINT:
            printf("Get a signal: SIGINT");
            break;
        case SIGQUIT:
            printf("Get a signal: SIGQUIT");
            break;
        default:
            printf("unknown signal");
            break;
    }

    return;
}

int main()
{
    signal(SIGHUP, sigrg);
    signal(SIGINT, sigrg);
    signal(SIGQUIT, sigrg);

    for(;;)
    {
        sleep(1);
    }

}