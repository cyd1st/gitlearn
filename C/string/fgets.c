#include <stdio.h>

char *fgets(char *s, int n,  FILE *stream)
{
    register int c;
    register char *cs;
    cs = s;
    while (--n > 0 && (c = getc(stream))! = EOF)
        if ((*cs++=  c) == '\n')
            break;
    *cs = '\0';
    return (c == EOF && cs == s) ? NULL : s;
}