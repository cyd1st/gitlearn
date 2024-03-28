/**
 * @file select_server.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-26
 * 
 * @copyright Copyright (c) 2024
 * 
 * 这份代码由 gpt 生成，是一个使用 select 的示例。
 * 这个示例创建了一个服务器，监听端口 8888。当有新的连接请求时，
 * 服务器会接受连接并打印连接信息。
 * 
 * 测试方法：
 *   使用 telnet/nc 或其他支持 TCP 的工具连接到服务器，并发送任意字符串。
 *   例如：telnet localhost 8888 或 nc localhost 8888。
 *
 * 压力测试方法：
 *   使用 ab（ApacheBench）或 siege 这样的工具来进行压力测试。
 *   这些工具可以模拟大量的并发连接，并测量服务器处理这些连接的能力。
 *   例如：ab -n 1000 -c 100 http://localhost:8888/ 来模拟 1000 个并发连接。
 *   实际运行这个命令很可能会超时。
 *
 * 知识点：
 *   []C标准库函数：如printf、exit、memset、strlen、read、write、close等。
 *   []套接字编程：理解什么是套接字（socket），以及如何使用C语言进行套接字编程。包括创建套接字、绑定套接字到服务器地址、监听连接请求、接受新的连接请求、读写数据等。
 *   []网络编程：理解网络编程的基本概念，如IP地址、端口号、TCP/IP协议等。需要掌握的相关函数和结构体包括sockaddr_in、htons、inet_ntoa等。
 *   []多客户端处理：理解如何使用select函数来同时处理多个客户端的连接。包括文件描述符集合的操作（如FD_ZERO、FD_SET、FD_ISSET等），以及select函数的使用。
 *   []错误处理：理解如何使用perror函数来打印错误信息，并使用exit函数来终止程序。
 */
#include <stdio.h>  // printf  
#include <stdlib.h> // exit EXIT_FAILURE
#include <string.h> // memset strlen
#include <unistd.h> // read write close
#include <sys/types.h>  // socket bind listen accept send
#include <sys/socket.h>
#include <netinet/in.h> // struct sockaddr_in htons
#include <arpa/inet.h>  // inet_ntoa

#define MAX_CLIENTS 1024
#define BUFFER_SIZE 1024 // 很多linux系统的最大文件描述符个数是1024，所以这里设定为1024

// 创建服务器套接字
int create_server_socket() {
    int server_socket;
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    return server_socket;
}

// 配置服务器地址
struct sockaddr_in configure_server_address() {
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8888);
    return server_addr;
}

// 绑定套接字到服务器地址
void bind_socket(int server_socket, struct sockaddr_in server_addr) {
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
}

// 监听连接请求
void listen_for_connections(int server_socket) {
    if (listen(server_socket, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

// 处理新的连接请求
void handle_new_connection(int server_socket, int *fd_array, fd_set *read_fds) {
    int client_socket;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    printf("New connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (fd_array[i] == 0) {
            fd_array[i] = client_socket;
            break;
        }
    }
}

// 处理新的数据
void handle_new_data(int *fd_array, fd_set *read_fds) {
    char buffer[BUFFER_SIZE];
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (FD_ISSET(fd_array[i], read_fds)) {
            memset(buffer, 0, BUFFER_SIZE);
            if (read(fd_array[i], buffer, BUFFER_SIZE) == 0) {
                close(fd_array[i]);
                fd_array[i] = 0;
            } else {
                // 如果读取到数据，再将其转发到其他所有的客户端
                for (int j = 0; j < MAX_CLIENTS; j++) {
                    if (fd_array[j] != 0) {
                        write(fd_array[j], buffer, strlen(buffer));
                    }
                }
            }
        }
    }
}

int main() {
    int server_socket = create_server_socket();
    struct sockaddr_in server_addr = configure_server_address();
    bind_socket(server_socket, server_addr);
    listen_for_connections(server_socket);

    // 客户端的fd集合
    int fd_array[MAX_CLIENTS] = {0};
    fd_set read_fds;

    printf("Waiting for connections...\n");

    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(server_socket, &read_fds);
        /** 
         * max_fd 表示已经处理的文件描述符的最大值 
         * select 函数需要这个值去遍历 0-max_fd
         */
        int max_fd = server_socket;
        // 初始化文件描述符的集合
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (fd_array[i] > 0) { // 是否是一个有效的文件描述符
                FD_SET(fd_array[i], &read_fds);
            }
            if (fd_array[i] > max_fd) {
                max_fd = fd_array[i];
            }
        }

        /**
         * 监听其中的可读 fd，其他的不监听。
         * 第一个参数 nfds 需要加1，是因为序列从0开始，所以max_fd序列大小要+1。
         */
        if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) < 0) {
            perror("select");
            exit(EXIT_FAILURE);
        }

        if (FD_ISSET(server_socket, &read_fds)) {
            handle_new_connection(server_socket, fd_array, &read_fds);
        }

        handle_new_data(fd_array, &read_fds);
    }

    return 0;
}
