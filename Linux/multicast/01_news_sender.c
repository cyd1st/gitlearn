#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> 

#define BUF_SIZE 100
#define TTL 64

void error_handling(const char *message);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage : %s <GroupIP> <PORT>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int send_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (send_sock == -1) {
        error_handling("scoket() error.");
    }

    // 设置发送端地址
    struct sockaddr_in mul_addr;
    memset(&mul_addr, 0, sizeof(mul_addr));
    mul_addr.sin_family = PF_INET;
    mul_addr.sin_addr.s_addr = inet_addr(argv[1]);
    mul_addr.sin_port = htons(atoi(argv[2]));

    // 设置多播TTL信息
    int time_live = TTL;
    setsockopt(send_sock, IPPROTO_IP, IP_MULTICAST_TTL, (void *)&time_live, sizeof(time_live));

    FILE *fp;
    if ((fp = fopen("01_news_sender.c", "r")) == NULL) {
        error_handling("failed open file.");
    }

    char buf[BUF_SIZE] = {0};
    while (!feof(fp)) {
        // read(int fd, void *buf, size_t nbytes)
        fgets(buf, BUF_SIZE, fp);
        sendto(send_sock, buf, strlen(buf), 0, (struct sockaddr *)&mul_addr, sizeof(mul_addr));
        sleep(2);
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