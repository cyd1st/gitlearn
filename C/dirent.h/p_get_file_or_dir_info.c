/*
* 功能：如果是文件，打印文件的一些信息。如果是目录，打印目录下的把内容。
*/

#include <stdio.h> // printf
#include <sys/stat.h> // S_ISDIR, S_ISREG, stat
#include <errno.h> // errno
#include <string.h> // strerror
#include <time.h> // ctime
#include <dirent.h> // opendir, readdir

int get_file_info(const char *filename)
{
    struct stat st;
    if (stat(filename, &st) == -1) {
        printf("Get stat on %s Error: %s\n",
                filename, strerror(errno));
        return -1;
    }
    if (S_ISDIR(st.st_mode)) return 1;
    if (S_ISREG(st.st_mode)) {
        printf("%s size: %ld bytes\tmodified at %s\n",
                filename, st.st_size, ctime(&st.st_mtime));
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int stat = 0;
    DIR *dir = NULL;
    struct dirent *de = NULL;

    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return -1;
    }
    if ((stat = get_file_info(argv[1])) == 0 || stat == -1) return -1;
    
    if ((dir = opendir(argv[1])) == NULL) {
        printf("Open directory %s Error: %s\n",
                argv[1], strerror(errno));
        return -1;
    }
    while ((de = readdir(dir)) != NULL) {
        printf("%s\t%u\n", de->d_name, de->d_type);
    }
    return 0;
}