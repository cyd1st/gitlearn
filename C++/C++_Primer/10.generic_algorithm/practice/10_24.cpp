#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;
using namespace std::placeholders;

bool check_size(int i, int sz)
{
    return i > sz;
}
vector<int>::const_iterator find_value_greater_string_size(const string &s, vector<int> &vi)
{
    auto sz = s.size();
    return find_if(vi.cbegin(), vi.cend(), bind(check_size, _1, sz));
}
int main()
{
    string s = "the";
    vector<int> vi = {2,1,3,1,5,67,78};
    auto it = find_value_greater_string_size(s, vi);
    cout << *it << endl;
}