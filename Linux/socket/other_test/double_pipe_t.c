#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFF_SIZE 100

int main()
{
    int parent_fds[2];
    int child_fds[2];
    pipe(parent_fds);
    pipe(child_fds);

    const char str1[] = "Hello world.";
    const char str2[] = "Hello Pipe.";

    char buf[BUFF_SIZE] = {0};

    pid_t pid = fork();
    if (pid == 0) {
        read(parent_fds[0], buf, BUFF_SIZE);
        printf("Child output: %s\n", buf);
        write(child_fds[1], str2, strlen(str2));
    } else {
        write(parent_fds[1], str1, strlen(str1));
        read(child_fds[0], buf, BUFF_SIZE);
        printf("Parent output: %s\n", buf);
    }

    return 0;
}