#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>

const int mem_size = sizeof(sem_t);

int main()
{
    int fd = open("mmap.data", O_CREAT | O_RDWR | O_TRUNC, 0777);
    lseek(fd, mem_size, SEEK_SET);
    write(fd, "", 1);

    sem_t *psem = (sem_t *)mmap(NULL, mem_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    int res = sem_init(psem, 1, 0);
    if (res != 0) {
        printf("sem_init error. %d %s\n", errno, strerror(errno));
        return -1;
    }

    while (true) {
        sleep(rand() % 10);
        printf("before post. ts:%ld\n", time(NULL));
        sem_post(psem);
    }

    res = sem_destroy(psem);
    assert(res != 0);

    munmap(psem, mem_size);
    printf("unmap.\n");

    return 0;
}