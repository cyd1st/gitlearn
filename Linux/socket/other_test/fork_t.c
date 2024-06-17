#include <stdio.h>
#include <unistd.h>

int gval = 10;

int main()
{
    int lval = 25;
    pid_t pid = fork();
    if (pid == 0) {
        // 子进程
        gval += 2;
        lval += 2;
    } else {
        gval -= 2;
        lval -= 2;
    }

    if (pid == 0) {
        printf("Child Proc: [%d, %d]\n", gval, lval);
    } else {
        printf("Parent Proc [%d %d]\n", gval, lval);
    }
    return 0;
}