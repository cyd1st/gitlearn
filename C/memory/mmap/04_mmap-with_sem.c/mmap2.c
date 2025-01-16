#include <fcntl.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>

const int mem_size = sizeof(sem_t);

int main()
{
    int fd = open("mmap.data", O_CREAT | O_RDWR, 0777);
    sem_t *psem = (sem_t *)mmap(NULL, mem_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    while (true) {
        printf("before wait. ts:%ld\n", time(NULL));
        sem_wait(psem);
    }

    sem_destroy(psem);
    munmap(psem, mem_size);

    return 0;
}