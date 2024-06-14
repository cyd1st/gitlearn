#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFF_SIZE 100

void error_handling(char *message);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uasge : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    int clnt_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (clnt_sock == -1) {
        error_handling("UDP socket create error.");
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    // 可以不使用
    if (connect(clnt_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) {
        error_handling("connect() error.");
    }

    char message[BUFF_SIZE + 1];
    struct sockaddr_in from_addr;
    socklen_t from_addr_size = sizeof(from_addr);
    size_t str_len = 0;
    while (1) {
        fputs("Insert message(q to quit): ", stdout);
        fgets(message, sizeof(message), stdin);
        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n")) {
            break;
        }
        sendto(clnt_sock, message, strlen(message), 0, 
            (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        str_len = recvfrom(clnt_sock, message, BUFF_SIZE, 0, 
            (struct sockaddr *)&from_addr, &from_addr_size);
        message[str_len] = 0;
        printf("Message from server: %s", message);
    }
    close(clnt_sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}