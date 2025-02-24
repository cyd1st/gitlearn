#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int sig) { printf("Signal %d interrupt sleep!\n", sig); }

int main()
{
    signal(SIGINT, handler);
    unsigned int remaining = sleep(10);
    if (remaining > 0) {
        printf("Sleep interrupt, remaining %d secoonds.\n", remaining);
    } else {
        printf("Sleep completed.\n");
    }
    return 0;
}