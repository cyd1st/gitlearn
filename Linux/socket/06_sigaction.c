#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void timeout(int sig)
{
    if (sig == SIGALRM) {
        puts("time out!");
    }
    alarm(2);
}

int main()
{
    struct sigaction act;
    act.sa_handler = timeout;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGALRM, &act, NULL);

    alarm(2);

    for (int i = 0; i < 3; i++) {
        puts("wait...");
        sleep(100);
    }

    return 0;
}