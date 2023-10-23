#include <stdio.h>

int main()
{
    typedef struct {
        int id;
        int age;
        int namelen;
        char name[];
    } Stu;

    Stu x;
    printf("x size: %lu\n", sizeof(x.name)); // x size: 8

    int nameLen = stelen("xiaoming");
    Stu *y = (Stu *)malloc(sizeof(Stu) + sizeof(char) * (nameLen + 1));
    y->id = 1;
    y->age = 18;
    y->namelen = nameLen;
    strcpy(y->name, "xiaoming");

    return 0;
}

