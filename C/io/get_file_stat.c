#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(void)
{
    const char *file_path = "./out/test.txt";
    const char *write_buf = "0123456789";
    FILE *f = fopen(file_path, "w");
    if (f == NULL) {
        perror("fopen() failed");
        return -1;
    } else {
        fwrite(write_buf, strlen(write_buf), 1, f);
        fclose(f);
    }

    struct stat file_stat;
    int ret = stat(file_path, &file_stat);
    if (ret == -1) {
        perror("stat() failed");
        return -1;
    }
    int file_size = file_stat.st_size;
    printf("file size: %d\n", file_size);
    return 0;
}