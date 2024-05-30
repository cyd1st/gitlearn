#include <stdio.h>

int main() {
    char cmd[] = "sort";
    char input[] = "banana\napple\norange\ngrape";

    FILE *stream = popen(cmd, "w");
    fwrite(input, sizeof(char), sizeof(input), stream);
}