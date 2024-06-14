#include <asm-generic/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

void error_handling(char *message);

int main()
{
    int tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    printf("SOCK_STREAM: %d\n", SOCK_STREAM);
    printf("SOCK_DGRAM: %d\n", SOCK_DGRAM);

    int sock_type;
    socklen_t optlen = sizeof(sock_type);
    int state = getsockopt(tcp_sock, SOL_SOCKET, SO_TYPE, (void *)&sock_type, &optlen);
    if (state) {
        error_handling("getsockopt() error!");
    }
    printf("Socket type one: %d \n", sock_type);

    state = getsockopt(udp_sock, SOL_SOCKET, SO_TYPE, (void *)&sock_type, &optlen);
    if (state) {
        error_handling("getsockopt() error!");
    }
    printf("Socket type one: %d \n", sock_type);
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}