#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <stdio.h>

int main()
{
    time_t rawtime;
    struct tm *broken_down_time;
    char buffer[80];

    // 获取当前时间（UTC时间）
    time(&rawtime);

    // 将 UTC 时间转换为本地时间
    broken_down_time = localtime(&rawtime);

    // 使用 strftime 格式化日期和时间
    if (strftime(buffer, sizeof(buffer), "%F %g", broken_down_time) > 0) {
        printf("Formatted time: %s\n", buffer);
    } else {
        fprintf(stderr, "Failed to format time\n");
    }

    printf("RAND_MAX = %ld\n", RAND_MAX);
    printf("1 rand() = %d\n", rand());
    printf("2 rand() = %d\n", rand());
    printf("3 rand() = %d\n", rand());

    // printf("rand_r = %d\n", rand_r())
    printf("rand_r = %d\n", rand_r((unsigned int *)&rawtime));

    return 0;
}
