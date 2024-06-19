#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#define FILENAME "sharedfile.txt"

int main() {
    FILE *file = fopen(FILENAME, "w+");
    if (!file) {
        perror("Failed to open file");
        return -1;
    }
    
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        fclose(file);
        return -1;
    } else if (pid == 0) { // 子进程
        fprintf(file, "Child writes this and exits...\n"); // 写入内容
        // 注意：这里使用exit可能会导致文件缓冲区被flush，以及可能的文件描述符关闭
        exit(0); 
    } else { // 父进程
        sleep(10); // 等待子进程先执行，确保子进程写入和退出
        fseek(file, 0, SEEK_SET); // 移动文件指针到开头，准备读取
        char buffer[100];
        fgets(buffer, sizeof(buffer), file);
        printf("Parent reads: %s", buffer);
        fclose(file);
    }

    return 0;
}