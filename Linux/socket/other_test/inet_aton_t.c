#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

// 传入 127.0.0.1
int main(int argc, char *argv[])
{
	if(argc != 2)
		exit(-1);

	struct in_addr addr;
    int ret = inet_aton(argv[1], &addr);
    printf("ret=%08x\n", ret);
	printf("0x%08x\n", addr.s_addr); // 0x0100007f
 
    exit(EXIT_SUCCESS);
}