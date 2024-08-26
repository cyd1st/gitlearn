#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>

#define SMALL_BUF 100
#define BUF_SIZE 1024

void error_handler(const char *msg);
void *request_handler(void *arg);
void send_error(FILE *fp);
char *content_type(const char *file);
void send_data(FILE *fp, char *ct, char *file_name);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handler("bind error.");
    }

    if (listen(serv_sock, 10) == -1) {
        error_handler("listen error.");
    }

    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock;
    pthread_t tid;
    while (1) {
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
        if (clnt_sock == -1) {
            fprintf(stderr, "accept client sock failed.\n");
            break;
        }

        printf("Connect Request : %s:%d\n", inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));

        pthread_create(&tid, NULL, request_handler, (void *)&clnt_sock);
        pthread_detach(tid);
    }

    close(serv_sock);
    return 0;
}

void error_handler(const char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

void *request_handler(void *arg)
{
    int clnt_sock = *(int *)arg;

    FILE *clnt_read = fdopen(clnt_sock, "r");
    FILE *clnt_write = fdopen(dup(clnt_sock), "w");

    char req_line[SMALL_BUF];
    fgets(req_line, SMALL_BUF, clnt_read);
    // debug
    printf("Get request data: %s\n", req_line);

    if (strstr(req_line, "HTTP/") == NULL) {
        goto CLOSE_CONNECT;
    }

    char method[10];
    char file_name[30]; // 要发送的数据（html网页）
    char ct[15]; // Connect-type, 连接类型

    strcpy(method, strtok(req_line, " /"));
    //debug
    printf("Get request method: %s\n", method);
    strcpy(file_name, strtok(NULL, " /"));
    // debug
    printf("Get request file name: %s\n", file_name);
    strcpy(ct, content_type(file_name));
    if (strcmp(method, "GET") != 0) {
        goto CLOSE_CONNECT;
    }
    fclose(clnt_read); // clnt_write 在 send_data 关闭
    send_data(clnt_write, ct, file_name);
    return NULL;

/**统一的关闭连接操作 */
CLOSE_CONNECT:
    send_error(clnt_write);
    fclose(clnt_read);
    fclose(clnt_write);
    return (void *)-1;
}

/**发送错误信息给客户端 */
void send_error(FILE *fp)
{
    char protocol[] = "HTTP/1.0 400 Bad Request\r\n";
    char server[] = "Server:Linux Web Server \r\n";
    char clnt_type[] = "Content-type:text/html\r\n\r\n";
    char clnt_len[] = "Content-length:2048\r\n";
    char content[] = "<html><head><title>NETWORK</title></head> \
        <body><font size=+5><br>发生错误！查看请求文件名和请求方式！</br></body> \
        </html>";

    fputs(protocol, fp);
    fputs(server, fp);
    fputs(clnt_len, fp);
    fputs(clnt_type, fp);
    fflush(fp);
}

char *content_type(const char *file)
{
    char extension[SMALL_BUF];
    char file_name[SMALL_BUF];

    strcpy(file_name, file);
    strtok(file_name, ".");
    strcpy(extension, strtok(NULL, "."));

    if (!strcmp(extension, "html") || !strcmp(extension, "htm")) {
        return "text/html";
    } else {
        return "text/plain";
    }
}

/**
 * ct: Content-type, 连接类型
 */
void send_data(FILE *fp, char *ct, char *file_name)
{
    char protocol[] = "HTTP/1.0 200 OK\r\n";
    char server[] = "Server:Linux Web Server \r\n";
    char clnt_len[] = "Content-length:2048\r\n";

    char clnt_type[SMALL_BUF];
    sprintf(clnt_type, "Content-type:%s\r\n\r\n", ct);
    FILE *send_file = fopen(file_name, "r");
    if (send_file == NULL) {
        send_error(fp);
        fclose(send_file);
        return;
    }

    /*传输头信息 */
    fputs(protocol, fp);
    fputs(server, fp);
    fputs(clnt_len, fp);
    fputs(clnt_type, fp);

    /*传输请求数据*/
    char buf[BUF_SIZE];
    while (fgets(buf, BUF_SIZE, send_file) != NULL) {
        fputs(buf, fp);
        fflush(fp);
    }
    fflush(fp);
    fclose(fp);
    fclose(send_file);
}

/* 用法：
 编译：gcc 03_webserv.c -o out/ws -lpthread && ./out/ws 12387
 运行：
    浏览器输入 http://127.0.0.1:12387/index.html
    index.html 文件需要自己提供。
*/