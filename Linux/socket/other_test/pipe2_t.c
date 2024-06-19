#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == 0) { // 子进程
        close(pipe_fd[1]); // 关闭写端
        char buffer[10];
        while (1) {
            ssize_t count = read(pipe_fd[0], buffer, sizeof(buffer)-1);
            if (count > 0) {
                buffer[count] = '\0';
                if (strcmp(buffer, "exit") == 0) {
                    printf("Child process: Exiting...\n");
                    break;
                }
            }
        }
        close(pipe_fd[0]); // 关闭读端并退出
        exit(0);
    } else { // 父进程
        close(pipe_fd[0]); // 关闭读端
        sleep(5); // 让子进程运行一段时间
        write(pipe_fd[1], "exit", 4); // 向子进程发送退出指令
        close(pipe_fd[1]); // 关闭写端并等待子进程结束
        wait(NULL);
    }
    return 0;
}
