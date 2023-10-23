#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("expect with 1 argument but %d\n", argc - 1);
        return -1;
    }
    
    char *file_path = argv[1];
    struct stat file_stat;
    int ret = stat(file_path, &file_stat);
    if (ret != 0) {
        printf("get file(%s)'s stat faild. error: %s\n", file_path, strerror(errno));
        return -1;
    }
    printf("file size = %.2fk\n", (float)file_stat.st_size / 1024);
    return 0;
}