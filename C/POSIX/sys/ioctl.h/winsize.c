// 获取终端的尺寸
// 运行后拖动窗口大小，可以看到输出变化。
#include <signal.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

struct winsize ws;

void handle_winch(int sig)
{
    int fd = fileno(stdout);
    if (ioctl(fd, TIOCGWINSZ, &ws) == 0) {
        printf("\r\33[2K窗口: %d行×%d列", ws.ws_row, ws.ws_col);
        fflush(stdout);
    } else {
        perror("\r\33[2K获取窗口大小失败");
        fflush(stdout);
    }
}

int main()
{
    int fd = fileno(stdout);

    if (ioctl(fd, TIOCGWINSZ, &ws) == 0) {
        printf("终端尺寸:\n");
        printf("字符行数 (ws_row): %d 行\n", ws.ws_row);
        printf("字符列数 (ws_col): %d 列\n", ws.ws_col);
        printf("像素高度 (ws_ypixel): %d px\n", ws.ws_ypixel);
        printf("像素宽度 (ws_xpixel): %d px\n", ws.ws_xpixel);
        printf("=====\n");
        fflush(stdout);
    } else {
        perror("获取终端尺寸失败");
        return 1;
    }

    signal(SIGWINCH, handle_winch);
    // 阻塞以保持程序运行
    while (1) {
        pause(); // 等待信号
    }

    return 0;
}