#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

int main()
{
    // 打开文件，O_RDWR表示读写模式，O_CREAT表示如果文件不存在则创建
    int fd = open("example.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // 改变文件大小为1024字节
    // 这个步骤非必须的。
    ftruncate(fd, 100);

    // 使用mmap将文件映射到内存，MAP_SHARED表示对映射区域的修改会反映到文件上
    void *mapped = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // 写入数据到映射区域
    strcpy(mapped, "Hello, mmap!");

    // 同步内存与文件，确保数据写入文件
    msync(mapped, 1024, MS_SYNC);

    // 解除映射
    munmap(mapped, 1024);

    // 关闭文件
    close(fd);

    return 0;
}
