#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFF_SIZE 1024
void error_handling(const char *message);

typedef struct stCalculateInfo {
    int cnt;
    char operator;
    int nums[10];
} CalculateInfo;

int get_caculate_info(CalculateInfo *out) {
    if (out == NULL) {
        fputs("Input NULL ptr.", stderr);
        return -1; 
    }

    int cnt;
    fputs("Input count: ", stdout);
    scanf("%d", &cnt);
    if (cnt > 10) {
        fputs("input operand count should less than 10.", stderr);
        return -1;
    }
    out->cnt = cnt;

    for (int i = 0; i < cnt; i++) {
        printf("Operand %d: ", i);
        scanf(" %d", &out->nums[i]);
    }

    char optr;
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    fputs("Input operator: ", stdout);
    scanf("%c", &optr);
    if (optr != '+' && optr != '-' && optr != '*' && optr != '/') {
        fprintf(stderr, "Please input vailed operator(%c)\n", optr);
        return -1;
    }
    out->operator = optr;

    return 0;
}

int SendToServer(int servScok, CalculateInfo data) {
    write(servScok, &data, sizeof(data));
    return 0;
}

int GetResFromServer(int servScok) {
    int res = 0;
    if (read(servScok, &res, sizeof(int)) != 0) {
        return res;
    } else {
        printf("Get result from server faild.\n");
        return -1;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[1]);
        exit(1);
    }

    
    char message[BUFF_SIZE];
    int str_len;

    int servSock = socket(PF_INET, SOCK_STREAM, 0);
    if (servSock == -1) {
        error_handling("socket() error.");
    }

    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htons(atoi(argv[2]));

    if (connect(servSock, (struct sockaddr *)&servAddr, sizeof(servAddr))) {
        error_handling("connect() error.");
    }

    while (1) {
        CalculateInfo data;
        if (get_caculate_info(&data) != 0) {
            fputs("Get calculate info failed.", stderr);
            break;
        }
        SendToServer(servSock, data);
        // usleep(1000);
        int res = GetResFromServer(servSock);
        printf("Get result from server: %d\n", res);
    }

    close(servSock);
    return 0;
}

void error_handling(const char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}