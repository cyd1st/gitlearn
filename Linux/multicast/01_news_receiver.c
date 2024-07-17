#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h> 

#define BUFF_SIZE 100

void error_handling(const char *message);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage : %s <GroupIP> <PORT>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // 设置 socket
    int recv_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (recv_sock == -1) {
        error_handling("socket() failed.");
    }
    struct sockaddr_in send_addr;
    memset(&send_addr, 0, sizeof(send_addr));
    send_addr.sin_family = PF_INET;
    send_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    send_addr.sin_port = htons(atoi(argv[2]));
    if (bind(recv_sock, (struct sockaddr *)&send_addr, sizeof(send_addr)) == -1) {
        error_handling("bind() error.");
    }

    // 设置 ip 多播组
    struct ip_mreq join_addr;
    join_addr.imr_multiaddr.s_addr = inet_addr(argv[1]); // 多播组IP
    join_addr.imr_interface.s_addr = htonl(INADDR_ANY); // 接收或者发送的地址
    setsockopt(recv_sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&join_addr, sizeof(join_addr));

    int str_len = 0;
    char buf[BUFF_SIZE] = {0};
    while (1) {
        str_len = recvfrom(recv_sock, buf, BUFF_SIZE - 1, 0, NULL, 0);
        if (str_len < 0) {
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