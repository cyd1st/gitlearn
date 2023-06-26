#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int mian()
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}