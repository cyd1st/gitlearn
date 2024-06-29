#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
    // int fd = open("./out/test.txt", O_WRONLY | O_CREAT | O_TRUNC);
    int fd = open("./out/test.txt", O_CREAT | O_EXCL);
    if (fd == -1) {
        fputs("file open failed.\n", stderr);
        printf("%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    FILE *fp = fdopen(fd, "w");
    fputs("Network C programming \n", fp);
    fclose(fp);
    return 0;
}

/**
 * test.txt 初始内容：
 * 123456789012345678901234567890
 * 
 * 执行后：
 * Network C programming 
 * 4567890
 */