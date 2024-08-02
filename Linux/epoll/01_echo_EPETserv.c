#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define EPOLL_SIZE 100
#define BUFF_SIZE 4 // 故意设置小，模拟需要边缘触发模式的场景

void error_handling(const char *msg);
void set_nonblocking_mode(int fd);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    int serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("scoket failed.");
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = PF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("bind socket failed.");
    }

    if (listen(serv_sock, 5) == -1) {
        error_handling("listen failed");
    }

    // 创建 epoll 文件
    int epoll_fd = epoll_create(EPOLL_SIZE);
    if (epoll_fd == -1) {
        error_handling("create epoll fd faield.");
    }
    struct epoll_event event = {
        .events = EPOLLIN,
        .data.fd = serv_sock
    };
    struct epoll_event *events = (struct epoll_event *)malloc(sizeof(struct epoll_event) * EPOLL_SIZE);
    if (events == NULL) {
        error_handling("malloc epoll events failed");
    }
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, serv_sock, &event) == -1) {
        error_handling("epoll_ctl add event error");
    }

    // 开始通过 epoll 异步处理客户端的连接
    int event_cnt = 0;
    struct epoll_event ctl_event; // 临时使用，传入到epoll_ctl函数中
    int clnt_scok = 0;
    struct sockaddr_in clnt_addr;
    socklen_t sz = 0; // clinet addr szie
    size_t read_len = 0; // read size of clnt socket
    char buf[BUFF_SIZE] = {0}; // read buff
    while (1) {
        event_cnt = epoll_wait(epoll_fd, events, EPOLL_SIZE, -1);
        if (event_cnt == -1) {
            perror("epoll_wait error.");
            break;
        }

        puts("return epoll_wait");
        for (int i = 0; i < event_cnt; i++) {
            // 如果是服务器sock有新的客户端连接，将客户端加入到events中
            if (events[i].data.fd == serv_sock) {
                clnt_scok = accept(serv_sock, (struct sockaddr *)&clnt_addr, &sz);
                set_nonblocking_mode(clnt_scok);
                ctl_event.data.fd = clnt_scok;
                // 此处添加了边缘触发模式
                ctl_event.events = EPOLLIN | EPOLLET;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, clnt_scok, &ctl_event);
                printf("connected client : %d \n", clnt_scok);
            } else {
                // 因为 BUFF SIZE 很小，所以一次可能读取不完。
                // 并且为边缘触发模式，只会在数据变化时通知一次，也就是说
                // 需要一次性读取完，不然如果文件描述符没有变化，就不会再通知了
                // 剩余数据就没法及时获取。
                // 
                // 边缘触发模式通常用于高性能服务器，需要处理大量的事件。
                // 因为如果是水平触发模式，一次没有处理完，下次该事件又会触发，
                // 影响性能。边缘触发模式可以降低同一事件被处理的次数，
                // 降低系统调用次数，也就提高了效率。
                // 
                // 另外，边缘触发模式需要将文件描述符设置为非阻塞，不然如果数据读取完了
                // 会等待数据，影响效率。
                // 那不管什么触发模式阻塞IO都会阻塞啊？为什么边缘触发模式要特别强调设置
                // 非阻塞IO呢？那是因为水平触发模式下，只要有数据都会触发事件，所以理论不会
                // 发生阻塞。但是边缘触发模式在获取（或发送）只会通知一次（触发事件一次），
                // 所以需要不断处理数据直到处理完，这时一定会出现阻塞（和LT模式相反），所以
                // 要强调ET模式下需要设置IO为非阻塞。如何判断数据是否处理完呢？下面的 EAGAIN
                // 处的注释会说明。
                while (1) {
                    read_len = read(events[i].data.fd, buf, BUFF_SIZE);
                    if (read_len == 0) {
                        // 读取完毕，关闭连接
                        epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, 0);
                        close(events[i].data.fd);
                        printf("closed client: %d\n", events[i].data.fd);
                        break;
                    } else if (read_len < 0) {
                        // 这是在处理边缘触发模式的“饥饿”问题，一直到吃完（或者写入）所有数据后。
                        // 这里的 EAGAIN 不用看作是报错，而是边缘触发模式的必然的路径。
                        // 因为设置了非阻塞IO + 当数据处理完了, 必然会出现 EAGAIN。
                        // 通过 EAGAIN 就可以判断数据是否处理完了。
                        if (errno == EAGAIN) {
                            // 非阻塞IO被阻塞了（即读取/写入不了数据），触发 EAGAIN
                            break;
                        }
                    } else {
                        write(events[i].data.fd, buf, read_len);
                    }
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

// 设置fd为非阻塞模式
void set_nonblocking_mode(int fd)
{
    int flag = fcntl(fd, F_SETFL, 0);
    fcntl(fd, F_SETFL, flag | O_NONBLOCK);
}

// 边缘触发模式似乎挺强的，水平触发模式还有什么用？
// 确实有一定道理，边缘触发对高并发的连接有很高的性能，
// 但伴随而来的是处理逻辑更复杂。如果服务本身就更简单，
// 也没有很高的性能指标，没必要使用边缘触发模式。