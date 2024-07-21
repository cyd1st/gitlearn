#include <fcntl.h>
#include <unistd.h>

int main()
{
    int flag = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flag | O_NONBLOCK); // 注销这行看看效果

    char buf[100];
    int res = read(STDIN_FILENO, buf, 100);
    return 0;
}
