#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

int main(int agrc, char *argv[])
{
    int serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = PF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    if (connect(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        exit(EXIT_FAILURE);
    }

    FILE *readfp = fdopen(serv_sock, "r");
    FILE *writefp = fdopen(serv_sock, "w");

    char buf[100];
    while (1) {
        if (fgets(buf, sizeof(buf), readfp) == NULL) {
            break;
        }
        fputs(buf, stdout);
        fflush(stdout);
    }

    // 读取结束后（服务器半关闭 SHUT_WR），向服务器写入数据
    fputs("From client~ \n", writefp);
    fflush(writefp);
    fclose(writefp);
    fclose(readfp);
    return 0;
}