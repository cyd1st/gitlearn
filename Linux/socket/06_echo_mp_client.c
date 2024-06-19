#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFF_SIZE 100

void error_handling(const char *message);
void write_routine(int sock, char *buf);
void read_routine(int sock, char *buf);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("crete socket failed.");
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    if (connect(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("connect serv addr failed.");
    }

    char buf[BUFF_SIZE];
    pid_t pid = fork();
    if (pid == 0) {
        write_routine(serv_sock, buf);
    } else {
        read_routine(serv_sock, buf);
    }

    close(serv_sock);
    return 0;
}

void read_routine(int sock, char *buf)
{
    while (1) {
        int len = read(sock, buf, BUFF_SIZE);
        if (len == 0) {
            return;
        }

        buf[len] = 0;
        printf("message from server: %s", buf);
    }
}

void write_routine(int sock, char *buf)
{
    while (1) {
        fgets(buf, BUFF_SIZE, stdin);
        if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n")) {
            // warnning: in sub process, need shutdown the sock.
            shutdown(sock, SHUT_WR);
            return;
        }
        write(sock, buf, strlen(buf));
    }
}

void error_handling(const char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}