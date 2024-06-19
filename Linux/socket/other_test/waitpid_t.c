#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        // Fork failed
        perror("fork");
        return 1;
    } else if (pid > 0) {
        // Parent process
        int status;
        waitpid(pid, &status, 0); // Wait for child to exit
        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        }
    } else {
        // Child process
        // exit(256); // Try changing this to -1 and see what happens
        exit(-1);
    }

    return 0;
}
