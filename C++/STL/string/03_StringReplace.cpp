#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

// 批量替换字符串中的字串
string &replaceAll(string &context, const string &from, const string &to)
{
    size_t lookHere = 0;
    size_t foundHere;
    while ((foundHere = context.find(from, lookHere)) != string::npos) {
        context.replace(foundHere, from.size(), to);
        lookHere = foundHere + to.size();
    }
    return context;
} ///:~

int main()
{
    string s("A piece of {s}.");
    string tag("{s}");

    int start = s.find(tag);
    s.replace(start, tag.size(), "string");
    cout << s << endl;

    string text = "a man, a plan, a canal, Panama.";
    replaceAll(text, "aa", "XXX");
    cout << text << endl;

    string text2 = "a man, a plan, a canal, Panama.";
    replace(text2.begin(), text2.end(), "a", "A");
    return 0;
}