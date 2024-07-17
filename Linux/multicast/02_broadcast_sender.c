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
        printf("Usage : %s <Broadcast IP> <PORT>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int send_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (send_sock == -1) {
        error_handling("socket() failed.");
    }
    struct sockaddr_in broad_addr;
    memset(&broad_addr, 0, sizeof(broad_addr));
    broad_addr.sin_family = PF_INET;
    broad_addr.sin_addr.s_addr = inet_addr(argv[1]);
    broad_addr.sin_port = htons(atoi(argv[2]));

    // 设置 socket 属性
    int so_brd = 1;
    setsockopt(send_sock, SOL_SOCKET, SO_BROADCAST, (void *)&so_brd, sizeof(so_brd));

    // open file and send
    FILE *fp = fopen("02_broadcast_sender.c", "r");
    if (fp == NULL) {
        error_handling("fopen failed.");
    }
    char buf[BUFF_SIZE];
    while (!feof(fp)) {
        fgets(buf, BUFF_SIZE, fp);
        sendto(send_sock, buf, strlen(buf), 0, (struct sockaddr *)&broad_addr, sizeof(broad_addr));
        // sleep(1);
        puts(buf);
    }

    fclose(fp);
    close(send_sock);
    return 0;
}

void error_handling(const char *message)
{
    fputs(message, stderr);
    putc('\n', stderr);
    exit(EXIT_FAILURE);
}
