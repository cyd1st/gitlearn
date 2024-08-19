#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <unistd.h>

#define MAX_CLNT 100
#define BUF_SZIE 256

pthread_mutex_t mutx;
int clnt_socks[MAX_CLNT];
int clnt_cnt = 0;

void error_handling(const char * msg);
void send_msg(char *msg, int len);
void *handle_clnt(void *arg);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(0);
    }

    pthread_mutex_init(&mutx, NULL);
    int serv_sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("bind serv socket failed.");
    }

    listen(serv_sock, 10);

    struct sockaddr_in clnt_addr;
    socklen_t clnt_size = sizeof(clnt_addr);
    int clnt_sock;
    pthread_t t_id;
    while (1) {
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_size);
        // 修改共享的变量需要加锁
        pthread_mutex_lock(&mutx);
        clnt_socks[clnt_cnt++] = clnt_sock;
        pthread_mutex_unlock(&mutx);
        // 创建线程处理新增的 client socket
        pthread_create(&t_id, NULL, handle_clnt, (void *)&clnt_sock);
        pthread_detach(t_id);
        printf("Connected clinet IP: %s:%d \n", inet_ntoa(clnt_addr.sin_addr), clnt_addr.sin_port);
    }
    close(serv_sock);
    return 0;
}

void error_handling(const char * msg)
{
    fputs(msg, stderr);
    putc('\n', stderr);
    exit(1);
}

void *handle_clnt(void *arg)
{
    int clnt_sock = *((int *)arg);
    int str_len = 0;
    char msg[BUF_SZIE];

    while ((str_len = read(clnt_sock, msg, sizeof(msg))) != 0) {
        send_msg(msg, str_len);
    }
    // 这里处理完就移除这个连接
    for (int i = 0; i < clnt_cnt; i++) {
        if (clnt_sock == clnt_socks[i]) {
            while (i < clnt_cnt - 1) {
                clnt_socks[i] = clnt_socks[i + 1];
            }
            break;
        }
    }
    clnt_cnt--;
    pthread_mutex_unlock(&mutx);
    close(clnt_sock);
    return NULL;
}

void send_msg(char *msg, int len)
{
    pthread_mutex_lock(&mutx);
    for (int i = 0; i < clnt_cnt; i++) {
        write(clnt_socks[i], msg, len);
    }
    pthread_mutex_unlock(&mutx);
}