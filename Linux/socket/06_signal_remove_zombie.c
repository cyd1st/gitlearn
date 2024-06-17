#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void read_childproc(int sig)
{
    int status = 0;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status)) {
        printf("Remove proc id: %d \n", pid);
        printf("Child send: %d \n", WEXITSTATUS(status));
    }
}

int main()
{
    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);

    pid_t pid = fork();
    if (pid == 0) {
        puts("Hi! I'm in child proc.");
        sleep(10);
        return 12;
    } else {
        printf("Child proc id: %d\n", pid);
        pid = fork();
        if (pid == 0) {
            puts("Hi! I'm child process");
            sleep(10);
            exit(24);
        } else {
            printf("Child proc id: %d\n", pid);
            for (int i = 0; i < 5; i++) {
                puts("wait...");
                sleep(5);
            }
        }
    }
    return 0;
}