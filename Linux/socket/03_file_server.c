#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFF_SIZE 100

void error_handling(char *message);
int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    FILE *fp = fopen("03_file_server.c", "rb");
    int serv_sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("bind error.");
    }

    listen(serv_sock, 6);

    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_szie = sizeof(clnt_addr);
    int clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_szie);

    int read_cnt = 0;
    char buf[BUFF_SIZE];
    while (1) {
        read_cnt = fread(buf, 1, BUFF_SIZE, fp);
        if (read_cnt < BUFF_SIZE) {
            write(clnt_sock, buf, read_cnt);
            break;
        }
        write(clnt_sock, buf, read_cnt);
    }

    shutdown(clnt_sock, SHUT_WR);
    read(clnt_sock, buf, BUFF_SIZE);
    printf("message from client: %s \n", buf);

    fclose(fp);
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}