#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFF_SIZE 100

void error_handling(const char *message);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[1]);
        exit(1);
    }

    int servSock = socket(PF_INET, SOCK_STREAM, 0);
    if (servSock == -1) {
        error_handling("socket() error.");
    }

    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htons(atoi(argv[2]));

    if (connect(servSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) != 0) {
        error_handling("connect() error.");
    }

    int str_len = 0;
    char message[BUFF_SIZE];
    while (1) {
        fgets(message, BUFF_SIZE, stdin);
        write(servSock, message, strlen(message));
        if ((str_len = read(servSock, message, BUFF_SIZE - 1)) != 0) {
            message[str_len] = 0;
            printf("Message from server: %s", message);
        }
    }
    
    close(servSock);
    return 0;
}

void error_handling(const char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}