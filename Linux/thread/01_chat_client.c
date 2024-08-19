#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define NAME_SIZE 64
#define BUF_SIZE 256

char name[NAME_SIZE];
char msg[BUF_SIZE]; // 这里不区分发送和接收的msg是为了使用mutex锁

void error_handling(const char * msg);
void *send_msg(void *arg);
void *recv_msg(void *arg);

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("Usage : %s <IP> <port> <name>\n", argv[0]);
        exit(1);
    }
    sprintf(name, "[%s]", argv[3]);
    
    // 创建服务器sock和addr
    int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    // 连接服务器
    if (connect(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("Connect to server error.");
    }

    // 分为发送和接收线程
    pthread_t th_send, th_recv;
    pthread_create(&th_send, NULL, send_msg, (void *)&serv_sock);
    pthread_create(&th_recv, NULL, recv_msg, (void *)&serv_sock);

    pthread_join(th_send, NULL);
    pthread_join(th_recv, NULL);

    close(serv_sock);
    return 0;
}

void error_handling(const char * msg)
{
    fputs(msg, stderr);
    putc('\n', stderr);
    exit(1);
}

void *send_msg(void *arg)
{
    int sock = *((int *)arg);
    char msg_with_name[BUF_SIZE + NAME_SIZE];

    while (1) {
        fgets(msg, BUF_SIZE - 1, stdin);
        if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n")) {
            close(sock);
            exit(0);
        }
        sprintf(msg_with_name, "%s %s", name, msg);
        write(sock, msg_with_name, strlen(msg_with_name));
    }
    return NULL;
}

void *recv_msg(void *arg)
{
    int sock = *((int *)arg);
    int str_len = 0;
    char msg_with_name[NAME_SIZE + BUF_SIZE];
    while (1) {
        str_len = read(sock, msg_with_name, NAME_SIZE + BUF_SIZE - 1);
        if (str_len == -1) {
            return (void *)-1;
        }
        msg_with_name[str_len] = '\0';
        fputs(msg_with_name, stdout);
    }
    return NULL;
}