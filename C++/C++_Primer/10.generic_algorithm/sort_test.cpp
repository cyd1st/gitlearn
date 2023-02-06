#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

bool isShorter(string &w1, string &w2)
{
    if (w1.size() == w2.size()) {
        return w1 < w2;
    }
    return w1.size() < w2.size();  
}

int main()
{
    vector<string> words = {
        "the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle", "theeeeht"
    };
    sort(words.begin(), words.end(), isShorter);
    for (auto &i : words)
        cout << i << " ";
    cout << endl;
    return 0;
}