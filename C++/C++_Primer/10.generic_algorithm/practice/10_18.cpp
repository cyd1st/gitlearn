#include <iostream>
#include <vector>

using namespace std;

vector<string>::iterator my_partition(vector<string> &words, bool p(const string &s))
{
    auto l = words.begin(), r = words.end() - 1;
    while (l < r) {
        while (p(*l)) l++;
        while (!p(*r)) r--;
        if (l < r) swap(*l, *r);
    }
    return l;
}

int main()
{
    vector<string> words = {
        "A", "bird", "is", "safe", "in",
        "its", "nest", "but", "that", "is", "not",
        "what", "its", "wings", "are", "made", "for"
    };
    auto ret = my_partition(words, [](const string &s) {
        if (s.size() < 3) return true;
        return false;
    });
    for (auto i = ret; i < words.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
    return 0;
}