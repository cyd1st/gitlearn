#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

int main()
{
    void *handle = dlopen("../out/libadd.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    int (*newAdd)(int, int);
    newAdd = dlsym(handle, "Add");
    if (newAdd == NULL) {
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        exit(EXIT_FAILURE);
    }

    printf("ret = %d\n", newAdd(100, 10));

    dlclose(handle);
    return 0;
}