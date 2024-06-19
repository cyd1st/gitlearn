#include <stdio.h>
#include <unistd.h>

#define BUFF_SIZE 30

int main()
{
    char buf[30] = {0};

    int fds[2];
    pipe(fds);

    pid_t pid = fork();
    if (pid == 0) {
        const char exam[] = "hello world.";
        write(fds[1], exam, sizeof(exam));
        sleep(2);
        read(fds[0], buf, BUFF_SIZE);
        printf("Child proc output: %s\n", buf);
    } else {
        read(fds[0], buf, BUFF_SIZE);
        puts(buf);
        const char exam[] = "thank you, fine.";
        write(fds[1], exam, sizeof(exam));
        sleep(3);
    }
    return 0;
}