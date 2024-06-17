#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void test_wait()
{
    int status;

    pid_t pid = fork();
    if (pid == 0) {
        puts("Hi, in child process.");
        sleep(20);
    } else {
        printf("Child pid: %d\n", pid);
        sleep(10);
        wait(&status);
        if (WIFEXITED(status)) {
            printf("child return: %d\n", WEXITSTATUS(status));
        }
    }

    if (pid == 0) {
        puts("end child process.");
    } else {
        puts("end parent process.");
    }
}

void test_waitpid()
{
    int status;
    pid_t pid = fork();
    if (pid == 0) {
        sleep(15);
        return;
    } else {
        pid_t t = waitpid(pid, &status, WNOHANG);
        printf("test: %d\n", t);
        while (!waitpid(pid, &status, WNOHANG)) {
            sleep(3);
            puts("sleep 3s.");
        }

        if (WIFEXITED(status)) {
            printf("Child return %d\n", WEXITSTATUS(status));
        }
    }
    return;
}

int main()
{
    
    // test_wait();
    test_waitpid();

    return 2;
}