#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFF_SIZE 100

void error_handling(const char *messgae);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("socket() error!");
    }

    struct sockaddr_in serv_addr;
    socklen_t serv_addr_size = sizeof(serv_addr);
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(serv_sock, (struct sockaddr *)&serv_addr, serv_addr_size) == -1) {
        error_handling("bind() error!");
    }
    if (listen(serv_sock, 6) == -1) {
        error_handling("listen() error.");
    }

    fd_set readfds, readfds_cp;
    FD_ZERO(&readfds);
    FD_SET(serv_sock, &readfds);
    int fd_max = serv_sock;
    struct timeval timeout;
    int fd_num;
    int clnt_sock;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int read_len = 0;
    char buf[BUFF_SIZE];

    while (1) {
        readfds_cp = readfds;
        timeout.tv_sec = 6;
        timeout.tv_usec = 10000;

        if ((fd_num = select(fd_max + 1, &readfds_cp, NULL, NULL, &timeout)) == -1) {
            break;
        }
        if (fd_num == 0) {
            continue;
        }

        for (int i = 0; i < fd_max + 1; i++) {
            if (FD_ISSET(i, &readfds_cp)) {
                if (i == serv_sock) {
                    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
                    FD_SET(clnt_sock, &readfds);
                    if (clnt_sock > fd_max) {
                        fd_max = clnt_sock;
                    }
                    printf("connected client(%d): %s(%d)\n", clnt_sock, inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));
                } else {
                    read_len = read(i, buf, BUFF_SIZE);
                    if (read_len == 0) {
                        FD_CLR(i, &readfds);
                        close(i);
                        printf("closed clinet: %d\n", i);
                    } else {
                        write(i, buf, read_len);
                    }
                }
            }
        }
    }
    close(serv_sock);
    return 0;
}

void error_handling(const char *messgae)
{
    fputs(messgae, stderr);
    putc('\n', stderr);
    exit(1);
}