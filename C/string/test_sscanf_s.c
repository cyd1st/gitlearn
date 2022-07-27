// 头文件：stdio.h  
// 函数原型：int sscanf_s(const char* buffer, const char* format);
// 如果成功，该函数返回成功匹配和赋值的个数。如果到达文件末尾或发生读错误，则返回 EOF。
// buffer要从中读取数据的缓冲区，format格式化控制字符串
// 如果格式化控制字符串（format）中包含了%s、%S、%c、%C或括号表达式（例如%[a-d]）时，函数中应该传入输出缓冲区长度大小(format之后)，
// 且长度大小必须小于等于输出缓冲区的实际大小、且大于等于（输出的数据长度 + 1）。
#include <stdio.h>
#include <string.h>
#include "securec.h"

#define DEST_LEN 100
#define SRC_LEN 100

int main()
{
    char strDest[DEST_LEN] = "192.168.1.100/24";
    int ip0 = 0;
    int ip1 = 0;
    int ip2 = 0;
    int ip3 = 0;
    int mask = 0;
    int ret = 0;
    // 入参需要传入地址
    ret = sscanf_s(strDest, "%d.%d.%d.%d/%d", &ip0, &ip1, &ip2, &ip3, &mask, DEST_LEN);
    // printf("strDest=%s, ret=%d, ip0=%d, ip1=%d, ip2=%d, ip3=%d, maske=%d\n", strDest, ret, ip0, ip1, ip2, ip3, mask);

    char strSrc[SRC_LEN] = "123456helloWORLD";
    char strTemp[SRC_LEN] = {0};
    // 字符匹配会被空格隔断, %5s——匹配5个字符； %[^o]——匹配到某个字符未止；%[a-z]——匹配a-z中的任意字符; %[^A-Z]——匹配除A-Z之外的任意字符
    // %[1-9a-z]——范围匹配， *表示跳过此数据不读入，否则完全从开始读入,如%*[1-9]%*[a-z]%s，获取123456helloWORLD中的大写字符串；
    ret = sscanf_s(strSrc, "%*[1-9]%*[a-z]%s", strTemp, SRC_LEN);
    // printf("strSrc=%s, ret=%d, temp=%s\n", strSrc, ret, strTemp);

    // %[^a]——匹配非a的任意字符， 配合*使用,%*[^a]，表示跳过字符串前面的非a的任意字符，后续处理从a开始
    ret = sscanf_s("ipadda=10.46.1.10/24", "%*[^=]=%d.%d.%d.%d/%d", &ip0, &ip1, &ip2, &ip3, &mask, DEST_LEN);
    //printf("ret=%d, ip0=%d, ip1=%d, ip2=%d, ip3=%d, maske=%d\n", ret, ip0, ip1, ip2, ip3, mask);
    // %*[ ] 可以去除空格
    memset(strTemp, 0, SRC_LEN);
    ret = sscanf_s("name   =    hzl", "%*[^=]=%*[ ]%s", strTemp, DEST_LEN);
    // printf("ret=%d, strTemp=%s\n", ret, strTemp);

    // 特殊数字匹配: 存在括号表达式时，需要在输出字符串后添加输出长度
    memset(strTemp, 0, SRC_LEN);
    char s1[SRC_LEN] = {0};
    char s2[SRC_LEN] = {0};
    ret = sscanf_s("1hello234world5", "%*[0-9]%[^2]234%[^5]", s1, SRC_LEN, s2, SRC_LEN);
    // printf("ret=%d, s1=%s, s2=%s\n", ret, s1, s2);

    // 跳过单个字符：%*c
    char s3[SRC_LEN] = {0};
    char s4[SRC_LEN] = {0};
    ret = sscanf_s("michale/nHao", "%[^/n]%*c%*c%s", s3, SRC_LEN, s4, SRC_LEN);
    printf("ret=%d, s3=%s, s4=%s\n", ret, s3, s4);

    return 0;
}
