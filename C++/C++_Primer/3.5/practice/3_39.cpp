#include <iostream>
#include <cstring>

using std::string;
using std::cout;
using std::endl;

int cmp_cstring(const char *s1, const char *s2)
{
    while (*s1 && *s2) {
        if (*s1 != *s2) {
            return (*s1 - *s2);
        }
        s1++;
        s2++;
    }
    if (!(*s1 || *s2)) {
        return 0;
    } else if (*s1 != '\0') {
        return 1;
    } else {
        return -1;
    }
}

int cmp_string(string s1, string s2)
{
    if (s1 > s2) {
        return 1;
    } else if (s1 < s2) {
        return -1;
    } else {
        return 0;
    }
}

int main()
{
    const char s1[] = "systemcappability.device.xx1";
    const char s2[] = "systemcappability.device.xx2";

    string ss1("hello world");
    string ss2("hello tomorrow");

    int ret = cmp_cstring(s1, s2);
    cout << "ret = " << ret << endl;

    ret = cmp_string(ss1, ss2);
    cout << "ret = " << ret << endl;

    return 0;
}