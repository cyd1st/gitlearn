#include <stdio.h>
#include <limits.h>

int main() {
    int max1 = -1;
    printf("%d\n", (unsigned int)max1 / 2);

    int max2 = ~(1 << 31);
    printf("%d\n", max2);

    int max3 = INT_MAX;
    printf("%d\n", max3);

    return 0;
}
