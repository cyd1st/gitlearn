
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Uasge : %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = PF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        exit(EXIT_FAILURE);
    }
    listen(serv_sock, 5);

    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = 0;
    int clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

    FILE *readfp = fdopen(clnt_sock, "r");
    FILE *writefp = fdopen(dup(clnt_sock), "w");

    fputs("from server: Hi~\n", writefp);
    fputs("What a nice day.\n", writefp);
    fflush(writefp);

    shutdown(fileno(writefp), SHUT_WR); // 无论 clnt_sock 复制了多少份，shutdwon 都是操作同一个文件描述符
    fclose(writefp);

    char buf[100];
    fgets(buf, sizeof(buf), readfp);
    fputs(buf, stdout);
    fclose(readfp);

    return 0;
}