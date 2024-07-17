#include <bits/types/struct_iovec.h>
#include <stdio.h>
#include <sys/uio.h>
#include <unistd.h>

int main()
{
    struct iovec vec[2];

    char buf1[] = "ABCDEFG";
    char buf2[] = "1234567";
    vec[0].iov_base = buf1;
    vec[0].iov_len = 4;
    vec[1].iov_base = buf2;
    vec[1].iov_len = 6;

    size_t str_len = writev(STDOUT_FILENO, vec, 2);
    puts(""); // 换行
    printf("Write bytes: %lu\n", str_len);
    return 0;
}