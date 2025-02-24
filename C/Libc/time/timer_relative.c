#include <bits/time.h>
#include <stdio.h>
#include <time.h>

void relative_time_demo()
{
    struct timespec delay = {1, 0}; // 1秒相对时间
    for (int i = 0; i < 5; i++) {
        // Assume task execute time is 0.2s
        // nanosleep(&delay, NULL); // Sleep for 1s each time
        clock_nanosleep(CLOCK_REALTIME, 0, &delay, NULL); // same with nanosleep
        printf("Cycle %d 完成\n", i + 1);
    }
}
// 结果：循环的实际间隔为 1.2秒（1秒休眠 + 0.2秒任务），总时间 6秒（5次 × 1.2秒）

int main()
{
    relative_time_demo();
    return 0;
}