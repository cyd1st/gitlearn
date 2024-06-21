#include <signal.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

void error_handling(const char *message);
void urg_handler(int sig);

int clnt_sock = -1;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage %s <port>\n", argv[0]);
        exit(1);
    }

    int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("socket() error.");
    }
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("bind() error.");
    }
    listen(serv_sock, 10);

    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
    fcntl(clnt_sock, F_SETOWN, getpid());

    struct sigaction act;
    act.sa_handler = urg_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    int state = sigaction(SIGURG, &act, 0);

    size_t str_len;
    char buf[100];
    while ((str_len = recv(clnt_sock, buf, sizeof(buf), 0)) != 0) {
        if (str_len == -1) {
            continue;
        }
        buf[str_len] = '\0';
        puts(buf);
    }

    close(clnt_sock);
    close(serv_sock);
    return 0;
}

void error_handling(const char *message)
{
    fputs(message, stderr);
    putc('\n', stderr);
    exit(1);
}

void urg_handler(int sig)
{
    char buf[100];
    int str_len = recv(clnt_sock, buf, sizeof(buf) - 1, MSG_OOB);
    buf[str_len] = '\0';
    printf("Urgent message: %s\n", buf);
}