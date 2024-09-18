#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void lambda_for_each(vector<string> &words)
{
    for_each(words.cbegin(), words.cend(), [](const string& s) {
        if (s.size() > 3) cout << s << " ";
    });
    cout << endl;
}

int lambda_stable_sort(vector<string> &words)
{
    stable_sort(words.begin(), words.end(), [](const string &a, const string &b) {
        {return a.size() < b.size();}
    });
    return 0;
}

int lambda_find_if(vector<string> &words)
{
    auto ret = find_if(words.begin(), words.end(), [](const string& w) {
        return w.size() > 2;
    });

    auto ret2 = find_if(words.cbegin(), words.cend(), [](const string& w) {
        return w.size() > 10;
    });

    cout << *ret << endl;
    if (ret2 == words.end())
        cout << "can't find the word which "
            "size greater than 10." << endl; 

    return 0;
}

int main()
{
    auto f = [] {
        int a = 1;
        return 3;
    };
    cout << f() << endl;

    vector<string> words = {
        "aaa", "bb", "fsfsgsdaw", "hjgyft", "sxdfv",
        "sfsfg", "dgdgdgd", "fdrstedrg", "zxghy"
    };
    lambda_stable_sort(words);
    for (auto &s : words) cout << s << " ";
    cout << endl;

    lambda_find_if(words);

    lambda_for_each(words);
    return 0;
}