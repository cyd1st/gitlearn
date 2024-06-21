#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void error_handling(const char *messgae);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sock_addr;
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = PF_INET;
    sock_addr.sin_addr.s_addr = inet_addr(argv[1]);
    sock_addr.sin_port = htons(atoi(argv[2]));
    if (connect(sock, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) == -1) {
        error_handling("connect() erorr.");
    }

    write(sock, "123", sizeof("123"));
    send(sock, "456", sizeof("456"), MSG_OOB);
    write(sock, "789", sizeof("789"));
    send(sock, "1011", sizeof("1011"), MSG_OOB);
    write(sock, "1213", sizeof("1213"));
    send(sock, "1213", sizeof("1213"), MSG_OOB);
    
    close(sock);
    return 0;
}

void error_handling(const char *messgae)
{
    fputs(messgae, stderr);
    putc('\n', stderr);
    exit(1);
}