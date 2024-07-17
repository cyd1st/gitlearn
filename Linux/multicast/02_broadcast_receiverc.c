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
    if (argc != 2) {
        printf("Usage : %s <PORT>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int recv_sock = socket(PF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in recv_addr;
    memset(&recv_addr, 0, sizeof(recv_addr));
    recv_addr.sin_family = PF_INET;
    recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    recv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(recv_sock, (struct sockaddr *)&recv_addr, sizeof(recv_addr)) == -1) {
        error_handling("bind() failed.");
    }

    int str_len = 0;
    char buf[BUFF_SIZE] = {0};
    while (1) {
        
        str_len = recvfrom(recv_sock, buf, BUFF_SIZE, 0, NULL, 0);
        if (str_len < 0) {
            perror("recvfrom() failed");
            break;
        } else if (str_len == 0) {
            // 可能是对方关闭了连接
            break;
        }
        buf[str_len] = 0;
        fputs(buf, stdout);
    }

    close(recv_sock);
    return 0;
}

void error_handling(const char *message)
{
    fputs(message, stderr);
    putc('\n', stderr);
    exit(EXIT_FAILURE);
}