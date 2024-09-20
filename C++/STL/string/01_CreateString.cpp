#include <cassert>
#include <string>

using namespace std;

int main()
{
    string s;
    assert(s.size() == 0 && s.length() == 0);

    string s1("aaa");
    string s2{"aaa"};
    string s3 = s1;
    assert(s1 == s2 && s1 == s3);

    string s4(s1, 0, 2);
    assert(s4 == "aa");

    string s5(s1.begin(), s1.end());
    assert(s5 == s1);

    string s6(3, 'a');
    assert(s6 == s1);

    return 0;
}