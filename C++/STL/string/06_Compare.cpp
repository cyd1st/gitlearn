#include <cassert>
#include <string>

using namespace std;

int main()
{
    string t("abcdefghij0123456789");
    string t2("abcdefghij");
    char cs[] = "abcdefghij";
    string t3("abcdefghij0");

    int ret = t.compare(t2);
    assert(ret > 0);

    ret = t.compare(cs);
    assert(ret > 0);

    ret = t.compare(0, 10, t2);
    assert(ret == 0);

    ret = t.compare(0, 10, cs);
    assert(ret == 0);

    ret = t.compare(0, 10, t3, 0, 10);
    assert(ret == 0);

    ret = t.compare(0, 10, cs, 0, 10);
    assert(ret == 0);

    ret = t.compare(0, 10, cs, 10);
    assert(ret == 0);

    assert(t3 >= t2); // c++20 开始废弃 > < >= <= 等重载

    return 0;
}

