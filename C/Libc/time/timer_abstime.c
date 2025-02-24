#include <time.h>

// execute precisely every second by using TIMER_ABSTIME
int main()
{
    struct timespec next;
    clock_gettime(CLOCK_MONOTONIC, &next);

    for (int i = 0; i < 10; i++) {
        next.tv_sec += 1;
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next, NULL);
    }
    return 0;
}