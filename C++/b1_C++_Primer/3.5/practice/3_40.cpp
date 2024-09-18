#include <iostream>
#include <cstring>

using std::string;
using std::cout;
using std::endl;

int main()
{
    char s1[100] = "hello ";
    char s2[] = "world.";
    char s3[100] = {0};

    strcpy(s3, s1);
    strcpy(s3 + strlen(s1), s2);

    strcat(s1, s2);
    cout << "strcpy : " << s3 << endl;
    cout << "strcat : " << s1 << endl;
    return 0;
}