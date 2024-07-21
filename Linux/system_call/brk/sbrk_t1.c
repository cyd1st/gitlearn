#include <unistd.h>
#include <stdio.h>

int main()
{
    long page_size = sysconf(_SC_PAGESIZE);
    printf("Page size: %ld\n", page_size);

    void *break_point = sbrk(0);
    printf("break point = %p\n", (void *)break_point);

    break_point = sbrk(page_size);
    printf("new page memory begin with = %p\n", (void *)break_point);

    break_point = sbrk(page_size);
    printf("new page memory begin with = %p\n", (void *)break_point);

    brk((char *)break_point + 1024);
    printf("new 1024 bytes by brk(), now break point = %p\n", sbrk(0));

    return 0;
}

/**
Page size: 4096
break point = 0x562aaec9b000
new page memory begin with = 0x562aaec9b000
new page memory begin with = 0x562aaec9c000
new 1024 bytes by brk(), now break point = 0x562aaec9c400
 */