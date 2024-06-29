#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 3 // 每次读写3字节

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage : %s <src> <dest>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *fp1 = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "w");

    char buf[BUFF_SIZE] = {0};
    while (fgets(buf, BUFF_SIZE, fp1) != NULL) {
        fputs(buf, fp2);
    }

    fclose(fp1);
    fclose(fp2);
    return 0;
}

/**
 * Generate 30M text file and test.
 *
 * dd if=/dev/urandom of=./out/testfile.txt bs=1M count=30
 * time ./out/a ./out/testfile.txt dest.txt
 * 
 *  real    0m0.933s
 *  user    0m0.742s
 *  sys     0m0.190s
 */