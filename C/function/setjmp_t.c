#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

void error_handler() {
    printf("Error occurred, jumping back.\n");
    longjmp(env, 100); // 发生错误时，使用 longjmp 回退
}

int main() {
    int result = setjmp(env);
    printf("setjmp result = %d\n", result);
    if (result == 0) { // 保存当前环境
        printf("Before error.\n");
        error_handler(); // 模拟错误处理
        printf("This line will not be reached.\n");
    } else if (result == 100) {
        printf("After error, control returned to main.\n");
    } else {
        printf("----.\n");
    }
    return 0;
}