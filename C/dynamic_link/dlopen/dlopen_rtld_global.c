#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

// 可以通过编译选项添加宏 -DGLOBAL，来看看区别。
// 说明：libuseadd.so 库中通过 dlopen 加载了 libadd.so 的内容
int main()
{
#ifdef GLOBAL
    void *handle = dlopen("../out/libadd.so", RTLD_LAZY | RTLD_GLOBAL);
#else
    void *handle = dlopen("../out/libadd.so", RTLD_LAZY | RTLD_LOCAL);
#endif
    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    void *handle2 = dlopen("../out/libuseadd.so", RTLD_LAZY);
    if (!handle2) {
        fprintf(stderr, "Error: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    void (*f)();
    f = dlsym(handle2, "UseAdd");
    f();

    dlclose(handle);
    dlclose(handle2);
    return 0;
}