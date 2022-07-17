#include "bubble_sort.h"

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int bubble_sort(int a[], size_t size)
{
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 -i; j++) { // 大的往后排，就是从小到大
            if (a[j] > a[j + 1]) { // 小的往后排，就是从小到大
                swap(&a[j], &a[j+1]);
            }
        }
    }
}