#include <netinet/in.h>
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
    if (argc != 3) {
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    FILE *fp = fopen("out/receive.dat", "wb");
    int local_sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(local_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0) {
        error_handling("connect error.");
    }

    char buf[BUFF_SIZE];
    int read_cnt = 0;
    while ((read_cnt = read(local_sock, buf, BUFF_SIZE)) != 0) {
        fwrite(buf, 1, read_cnt, fp);
    }
    puts("received file data");
    write(local_sock, "Finish.", 8);
    fclose(fp);
    close(local_sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}