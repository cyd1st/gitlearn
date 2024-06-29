#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFF_SIZE 3 // 每次读写3字节

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage : %s <src> <dest>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC);

    size_t len = 0;
    char buf[BUFF_SIZE] = {0};
    while ((len = read(fd1, buf, sizeof(buf))) > 0 ) {
        write(fd2, buf, len);
    }

    close(fd1);
    close(fd2);
    return 0;
}

/**
 * Generate 30M text file and test.
 *
 * dd if=/dev/urandom of=./out/testfile.txt bs=1M count=30
 * time ./out/a ./out/testfile.txt dest.txt
 *
 *  real    0m24.532s
 *  user    0m6.919s
 *  sys     0m17.609s
 */