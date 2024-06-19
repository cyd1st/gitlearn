#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFF_SIZE 100

void error_handling(const char *message);
void read_childproc(int sig);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Uasge %s <port> \n", argv[0]);
        exit(1);
    }

    // 注册信号处理函数，用于处理子进程结束发出的信号
    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);

    // create server socket.
    int serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("Create socket failed.");
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("bind() error.");
    }
    if (listen(serv_sock, 5) == -1) {
        error_handling("listen() error.");
    }

    // 创建管道和子进程来接受并保存数据
    int fds[2];
    pipe(fds);
    pid_t pid = fork();
    if (pid == 0) {
        // 子进程用来接受并保存数据
        FILE *fp = fopen("./out/recv.txt", "wt");
        char msgbuf[BUFF_SIZE];
        int len;
        for (int i = 0; i < 10; i++) {
            len = read(fds[0], msgbuf, BUFF_SIZE);
            fwrite(msgbuf, 1, len, fp);
        }
        fclose(fp);
        return 0;
    }


    int clnt_sock;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_szie = sizeof(clnt_addr);
    char buf[BUFF_SIZE];
    int read_len = 0;
    while (1) {
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_szie);
        if (clnt_sock == -1) {
            continue;
        } else {
            printf("new connected client: %s:%d\n", inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));
        }

        pid = fork();
        if (pid == 0) {
            // 子进程不需要 serv_sock，及时关闭以免资源泄露。
            close(serv_sock);
            while ((read_len = read(clnt_sock, buf, BUFF_SIZE)) != 0) {
                write(clnt_sock, buf, read_len);
                write(fds[1], buf, read_len);
            }

            close(clnt_sock);
            printf("client(%s:%d) disconnect..\n", inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));
            return 0;
        } else {
            close(clnt_sock);
        }
    }
}

void error_handling(const char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

// 处理子进程结束的信号
void read_childproc(int sig)
{
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    if (WEXITSTATUS(status)) {
        printf("Remove proc id: %d\n", pid);
        printf("Child send: %d\n", WEXITSTATUS(status));
    }
}