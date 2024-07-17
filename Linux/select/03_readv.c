#include <bits/types/struct_iovec.h>
#include <stdio.h>
#include <sys/uio.h>
#include <unistd.h>

int main()
{
    struct iovec vec[2];

    char buf1[10] = {0};
    vec[0].iov_base = buf1;
    vec[0].iov_len = 5;

    char buf2[10] = {0};
    vec[1].iov_base = buf2;
    vec[1].iov_len = 10;

    size_t str_len = readv(STDIN_FILENO, vec, 2);

    puts(""); // 换行
    printf("str_len = %lu\n", str_len);
    printf("buf1 = %s\n", buf1);
    printf("buf2 = %s\n", buf2);

    scanf("%*s");

    return 0;
}