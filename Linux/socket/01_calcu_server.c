#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <threads.h>
#include <unistd.h>

#define BUFF_SIZE 1024 
void error_handling(const char *message);

typedef struct stCalculateInfo {
    int cnt;
    char operator;
    int nums[10];
} CalculateInfo;

int GetCalculateInfo(int clntSock, CalculateInfo *out) {

    if (read(clntSock, out, sizeof(CalculateInfo)) == 0) {
        return -1;
    }

    return 0;
}

int CalculateNumsPLus(int *nums, int cnt) {
    if (cnt == 0) return 0;
    int res = nums[0];

    for (int i = 1; i < cnt; i++) {
        res += nums[i];
    }

    return res;
}

int CalculateNumsSub(int *nums, int cnt) {
    if (cnt == 0) return 0;
    int res = nums[0];

    for (int i = 1; i < cnt; i++) {
        res -= nums[i];
    }

    return res;
}

int CalculateNumsMul(int *nums, int cnt) {
    if (cnt == 0) return 0;
    int res = nums[0];

    for (int i = 1; i < cnt; i++) {
        res *= nums[i];
    }

    return res;
}

int CalculateNumsDiv(int *nums, int cnt) {
    if (cnt == 0) return 0;
    int res = nums[0];

    for (int i = 1; i < cnt; i++) {
        res /= nums[i];
    }

    return res;
}

int CalculateNums(CalculateInfo in) {
    printf("calculate cnt: %d: ", in.cnt);
    for(int i = 0; i < in.cnt; i++) {
        printf("%d ", in.nums[i]);
    }
    printf("\n");

    switch (in.operator) {
        case '+':
            return CalculateNumsPLus(in.nums, in.cnt);
            break;
        case '-':
            return CalculateNumsSub(in.nums, in.cnt);
            break;
        case '*':
            return CalculateNumsMul(in.nums, in.cnt);
            break;
        case '/':
            return CalculateNumsDiv(in.nums, in.cnt);
            break;
        default:
            return 0;
    }
}

int SendResToClient(int clntSock, int res) {
    write(clntSock, &res, sizeof(int));
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
    }

    int clnt_sock;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char message[BUFF_SIZE] = {0};

    // 创建 socket
    int serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("socket() error.");
    }

    // 设置服务器地址
    /**
     * Q: 为什么需要先清空呢？
    *    A: 因为只会设置一部分，其他部分不初始化，会有未定义行为。
     * Q: 为什么设置需要hton系列函数，为什么 sin_family 不需要？
     */
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("bind() error.");
    }

    if (listen(serv_sock, 5) == -1) {
        error_handling("listen() error.");
    }

    clnt_addr_size = sizeof(clnt_addr);
    /**
     * Q: 为什么需要将 clnt_addr 转为 struct sockaddr类型，而不是直接设置 struct sockaddr？
     *    A: 因为没法直接设置，struct sockaddr 只有前几个字段是有意义的，后面都是大段的单字节数组。
     *       为什么这么设计？因为这样 struct sockaddr 可以根据前几个字节分析后面的单字节序列按照什么规则
     *       处理，这样就可以传入不同的协议类型，只要保持前几个字段一样就行。比如这里的 sockaddr_in
     *       通常就表示 ipv4。
     */

    for (int i = 0; i < 5; i++) {
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        if (clnt_sock == -1) {
            error_handling("accept() error.");
        }
        printf("connect client  %d\n", i);

        CalculateInfo data;
        while (GetCalculateInfo(clnt_sock, &data) == 0) {
            int res = CalculateNums(data);
            printf("Calculate result is %d\n", res);
            SendResToClient(clnt_sock, res);
        }
        close(clnt_sock);
    }

    
    close(serv_sock);
    return 0;
}

void error_handling(const char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}