#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

void error_handling(char *message);

void PrintfSocketBuffer(int sock)
{
    int sock_send_buf;
    socklen_t optlen = sizeof(sock_send_buf);
    int state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void *)&sock_send_buf, &optlen);
    if (state) {
        error_handling("getsockopt() error!");
    }
    printf("Socket send buffer: %d KB\n", sock_send_buf / 1024);

    state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void *)&sock_send_buf, &optlen);
    if (state) {
        error_handling("getsockopt() error!");
    }
    printf("Socket recv buffer: %d KB\n", sock_send_buf / 1024);
}

void SetSocketBuffer(int sock)
{
    int state;
    int sned_buf = 32 * 1024;
    state = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void *)&sned_buf, sizeof(sned_buf));
    if (state) {
        error_handling("setsockopt SO_SNDBUF failed.");
    }

    int recv_buf = 100 * 1024;
    state = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void *)&recv_buf, sizeof(recv_buf));
    if (state) {
        error_handling("setsockopt SO_RECVBUF failed.");
    }
}

int main()
{
    int tcp_sock = socket(AF_INET, SOCK_STREAM, 0);

    PrintfSocketBuffer(tcp_sock);
    SetSocketBuffer(tcp_sock);
    PrintfSocketBuffer(tcp_sock);

    close(tcp_sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}