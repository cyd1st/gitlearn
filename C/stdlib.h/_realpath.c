
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int main()
{
    char *rpath = "./../a";
    char apath[PATH_MAX + 1];
    char *ret = realpath(rpath, apath);

    printf("ret = %s\n", ret);
    printf("apath = %s\n", apath);
    printf("errno = %s\n", errno == EACCES ? "EACCES" :
                           errno == ENOENT ? "ENOENT" :
                           "??");
    return 0;
}