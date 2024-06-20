#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>

#define BUFF_SIZE 100

int main()
{
    struct timeval timeout;
    fd_set reads, temps;
    char buf[BUFF_SIZE];
    int result;
    int str_len;

    FD_ZERO(&reads);
    FD_SET(0, &reads);    

    while (1) {
        temps = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 5000;
        
        result = select(1, &temps, NULL, NULL, &timeout);
        if (result == -1) {
            puts("select() error.");
            break;
        } else if (result == 0) {
            puts("select() timeout.");
            break;
        } else {
            if (FD_ISSET(0, &temps)) {
                str_len = read(0, buf, BUFF_SIZE);
                buf[str_len - 1] = '\0'; // '\n' -> '\0'
                puts(buf);
            }
        }
    }

    return 0;
}