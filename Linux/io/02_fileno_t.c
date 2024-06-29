#include <stdio.h>
#include <fcntl.h>

int main()
{
    int fd = open("./out/test.txt", O_RDONLY);
    printf("fd = %d\n", fd);

    FILE *fp = fdopen(fd, "r");

    int fd2 = fileno(fp);
    printf("fd2 = %d\n", fd2);

    return 0;
}