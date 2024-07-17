#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_EPOLL_SIZE 100
#define BUFF_SIZE 4 // 防止一次性接收全部数据，无法体现实验价值

void error_handling(const char *msg);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    } 

    int serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("create socket failed.");
    }
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("bind error.");
    }
    if (listen(serv_sock, 2) == -1) {
        error_handling("listen error.");
    }

    // 创建 epoll
    int epoll_fd = epoll_create(100);
    struct epoll_event event = {
        .events = EPOLLIN,
        .data.fd = serv_sock
    };
    int ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, serv_sock, &event);
    if (ret == -1) {
        error_handling("epoll control failed.");
    }

    char buf[BUFF_SIZE] = {0};
    struct epoll_event *ep_events = (struct epoll_event *)malloc(sizeof(struct epoll_event) * MAX_EPOLL_SIZE);
    //避免每次循环都创建变量，所以在while循环外
    struct sockaddr_in clnt_addr;
    socklen_t clnt_sz = sizeof(clnt_addr);
    while (1) {
        int event_cnt = epoll_wait(epoll_fd, ep_events, MAX_EPOLL_SIZE, -1);
        if (event_cnt == -1) {
            puts("epoll_wait error");
            break;
        }
        puts("return epoll wait");
        for (int i = 0; i < event_cnt; i++) {
            if (ep_events[i].data.fd == serv_sock) {
                // 新增 client，并添加 epoll 监听
                int clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_sz);
                event.events = EPOLLIN; // 开启边缘触发（可以关闭后对比第61行的打印次数）
                event.data.fd = clnt_sock;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, clnt_sock, &event);
                printf("connect client: %d\n", clnt_sock);
            } else {
                // 已连接的 client 有数据接收到缓冲区
                size_t strlen = read(ep_events[i].data.fd, buf, BUFF_SIZE);
                if (strlen == 0) {
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
                    close(ep_events[i].data.fd);
                    printf("closed client: %d\n", ep_events[i].data.fd);
                } else {
                    write(ep_events[i].data.fd, buf, strlen); // echo
                }
            }
        }
    }

    close(serv_sock);
    close(epoll_fd);
    return 0;
}

void error_handling(const char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(EXIT_FAILURE);
}