#include <iostream>
#include <map>
#include <string>
#include <set>

using namespace std;

void words_counter_exclude()
{
    map<string, int> mp;
    set<string> exclude_words = {"the", "aa"};
    string word;
    while (cin >> word) {
        if (exclude_words.find(word) == exclude_words.end())
            ++mp[word];
    }
    for (const auto &s : mp) {
        cout << s.first << " " << "occurs "
            << s.second << ((s.second > 1) ? " times" : " time") << endl;
    }
}

void words_counter()
{
    map<string, int> mp;
    string word;
    while (cin >> word) {
        ++mp[word];
    }
    for (const auto &s : mp) {
        cout << s.first << " " << "occurs "
            << s.second << ((s.second > 1) ? " times" : " time") << endl;
    }
}
int main()
{
    // words_counter();
    words_counter_exclude();
    return 0;
}