#include <stdio.h>

int main() {
    char cmd[] = "ping baidu.com";
    char buff[10];

    FILE *stream = popen(cmd, "r");
    while (fgets(buff, sizeof(buff), stream)) {
        fprintf(stdout, "%s", buff);
    }
    pclose(stream);
}