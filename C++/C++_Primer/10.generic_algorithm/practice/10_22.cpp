#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;
using namespace std::placeholders;

bool check_size(const string& s, string::size_type sz)
{
    return s.size() <= sz;
}

int bind_count_if()
{
    vector<string> vs = {
        "qqqqqqqq",
        "fffff",
        "jkkkkk",
        "sfsf",
        "nwsf",
        "pq",
        "kkk"
    };
    auto check_size6 = bind(check_size, _1, 6);
    return count_if(vs.cbegin(), vs.cend(), check_size6);
}
int main()
{
    cout << bind_count_if() << endl;
    return 0;
}