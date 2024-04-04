#include <stdlib.h> // free
#include <stdio.h> // printf
#include <unistd.h> // getcwd
#include <fcntl.h> // O_RDONLY, open

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDONLY);
    fchdir(fd);

    char *cwd = getcwd(NULL, 0);
    printf("current working directory: %s\n", cwd);
    free(cwd);
    return 0;
}