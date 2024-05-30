#include <iostream>

void bubble_sort(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 1; j < size - i; j++) {
            if (arr[j] < arr[j - 1]) {
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            }
        }
    }
}

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