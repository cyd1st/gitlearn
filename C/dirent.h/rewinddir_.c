#include <dirent.h> // rewinddir
#include <stdio.h>

int main(int argc, char **argv)
{
    DIR *dir = opendir(argv[1]);
    struct dirent *ptr = NULL;
    printf("file in %s: \n", argv[1]);
    while ((ptr = readdir(dir)) != NULL) {
        printf("%s\n", ptr->d_name);
    }

    rewinddir(dir);
    printf("---------- read dir again ---------\n");
    while ((ptr = readdir(dir)) != NULL) {
        printf("%s\n", ptr->d_name);
    }

    closedir(dir);
    return 0;
}