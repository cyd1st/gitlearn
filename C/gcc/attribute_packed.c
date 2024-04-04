#include <stdio.h>

int main()
{
    struct st1 {
        char c[5];
        int i;
    };

    printf("sizeof(st1) = %llu\n", sizeof(struct st1)); // sizeof(st1) = 12

    struct st2 {
        char c[5];
        int i;
    } __attribute__((__packed__));

    printf("szieof(st2) = %llu\n", sizeof(struct st2)); // szieof(st2) = 9

    return 0;
}