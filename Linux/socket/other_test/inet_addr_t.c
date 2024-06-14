#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>

void test_inet_addr()
{
    const char ip1[] = "1.2.3.256";

    in_addr_t res =  inet_addr(ip1);
    if (res == INADDR_NONE) {
        printf("trans string(%s) ip to uint failed.\n", ip1);
    } else {
        printf("unsigned ip : %u\n", res);
    }
}

void test_inet_aton() 
{
    const char ip1[] = "1.2.3.4";
    struct sockaddr_in sock_addr;

    int res = inet_aton(ip1, &sock_addr.sin_addr);
    if (res) {
        printf("%#x\n", sock_addr.sin_addr.s_addr);
    } else {
        printf("failed.\n");
    }
}
int main() {
    test_inet_aton();

    return 0;
    
}
