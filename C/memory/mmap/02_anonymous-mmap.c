// Parent child processes shared anonymous memory

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

int main()
{
    // need flags MAP_SHARED | MAP_ANONYMOUS 
    char *sm = (char *)mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (fork() == 0) {
        // child process
        sleep(1);
        printf("%s\n", sm);
        sprintf(sm, "%s", "this's from child.");
        exit(0);
    }

    sprintf(sm, "%s", "this's from parent.");
    sleep(2);
    printf("%s\n", sm);
    // parent and child process manage mmap together
    munmap(sm, 1024);
    return 0;
}