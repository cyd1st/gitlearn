#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/*
malloc memory size always greater than request size.
*/
int main() {
    size_t request_size = 100;
    void *ptr = malloc(request_size);
    if (ptr != NULL) {
        size_t actual_size = malloc_usable_size(ptr);
        printf("Requested size: %zu, Actual usable size: %zu\n", request_size, actual_size);
        free(ptr);
    }
    return 0;
}