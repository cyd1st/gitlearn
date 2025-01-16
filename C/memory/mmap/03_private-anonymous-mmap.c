// private anonymoous mmap equal to malloc.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#define MAP_SIZE 4096 // one page 4K

int main()
{
    int prot = PROT_READ | PROT_WRITE;
    int flags = MAP_PRIVATE | MAP_ANONYMOUS;

    void *map_address = mmap(NULL, MAP_SIZE, prot, flags, -1, 0);
    if (map_address == NULL) {
        perror("Private anonymous failed.");
        exit(EXIT_FAILURE);
    }

    printf("Mappepd new anoymous memory at address: %p\n", map_address);

    char *message = "Hello Mmap";
    strncpy(map_address, message, strlen(message) + 1);

    printf("Read from mapped address: %s\n", (char *)map_address);

    if (munmap(map_address, MAP_SIZE) != 0) {
        perror("Unmap failed.");
        exit(EXIT_FAILURE);
    }

    return 0;
}