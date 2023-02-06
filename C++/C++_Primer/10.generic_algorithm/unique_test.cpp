#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> words = {
        "the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle", "the"
    };

    sort(words.begin(), words.begin() + 10);
    cout << words.size() << endl;
    for (auto &i : words)
        cout << i << " ";
    cout << endl;

    auto end_unique = unique(words.begin(), words.begin() + 10);
    cout << words.size() << endl;
    for (auto &i : words)
        cout << i << " ";
    cout << endl;

    return 0;
}

/* the result: why?
10
fox jumps over quick red red slow the the turtle 
10
fox jumps over quick red slow the turtle the 
becase: unique copy the words.end() to the end. and the words.end() == "".
*/