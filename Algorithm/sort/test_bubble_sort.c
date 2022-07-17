#include <stdio.h>
#include "bubble_sort.h"

int main()
{
    int a[] = {3,5,76,754,36,7,2,647,7,33,8,7};
    size_t size = sizeof(a)/sizeof(a[0]);
    printf("size = %lu\n", size);
    bubble_sort(a, size);
    for (int i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}