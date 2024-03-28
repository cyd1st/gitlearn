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
 */
#include <stdio.h>  // printf  
#include <stdlib.h> // exit EXIT_FAILURE
#include <string.h> // memset strlen
#include <unistd.h> // read write close
#include <sys/types.h>  // socket bind listen accept send
#include <sys/socket.h>
#include <netinet/in.h> // struct sockaddr_in htons
#include <arpa/inet.h>  // inet_ntoa

#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

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

    int fd_array[MAX_CLIENTS] = {0};
    fd_set read_fds;

    printf("Waiting for connections...\n");

    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(server_socket, &read_fds);
        int max_fd = server_socket;
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (fd_array[i] > 0) {
                FD_SET(fd_array[i], &read_fds);
            }
            if (fd_array[i] > max_fd) {
                max_fd = fd_array[i];
            }
        }

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
