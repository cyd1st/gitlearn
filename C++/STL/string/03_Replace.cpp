#include <algorithm>
#include <iostream>
#include <string>
#include "03_ReplaceAll.h"
using namespace std;

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
    replace(text2.begin(), text2.end(), 'a', 'A');
    cout << text2 << endl;

    string text3 = "a man, a plan, a canal, a Panama.";
    replaceAll(text3, "a ", "");
    cout << text3 << endl;

    return 0;
}