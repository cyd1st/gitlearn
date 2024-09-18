#include <iostream>
#include <functional>
#include <ostream>
#include <vector>
#include <algorithm>

using namespace std;
using namespace std::placeholders;

void print(const string& s, ostream& os, int n)
{
    if (s.size() > n)
        os << s << " ";
}

void print_size_greater_n(vector<string> &vs, ostream &os, int n)
{
    for_each(vs.begin(), vs.end(), [&os, n](const string &s) {
        if (s.size() > n) os << s << " ";
    });
    os << endl;

    for_each(vs.begin(), vs.end(), bind(print, _1, ref(os), n));
    os << endl;
}

bool check_size(const string& s, int sz)
{
    return s.size() > sz;
}

void find_if_size6(vector<string> &vs, int sz)
{
    auto bind_func = bind(check_size, _1, sz);

    auto t1 = find_if(vs.begin(), vs.end(), bind_func);
    cout << *t1 << endl;

    auto t2 = find_if(vs.begin(), vs.end(), [sz](const string& s) {
        return s.size() > sz;
    });
    cout << *t2 << endl;
}

int main()
{
    vector<string> vs = {
        "qqqq",
        "ww",
        "aaaaa",
        "fffffff",
        "cvd",
        "c"
    };
    find_if_size6(vs, 6);

    print_size_greater_n(vs, cout, 3);
    return 0;
}