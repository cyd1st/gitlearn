#include <stdio.h>

int main() {
    char cmd[] = "ls -lR ./";
    char buff[256];

    FILE *stream = popen(cmd, "r");
    while (fgets(buff, sizeof(buff), stream)) {
        fprintf(stdout, "%s", buff);
    }
    pclose(stream);
}