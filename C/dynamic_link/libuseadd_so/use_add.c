#include <dlfcn.h>
#include <stdio.h>

void UseAdd()
{
    int (*MyAdd)(int, int);
    MyAdd = (int (*)(int, int))dlsym(RTLD_DEFAULT, "Add");
    printf("Use Add result : %d\n", MyAdd(100, 12));
}