#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>

using namespace std;

string trim(const string &s)
{
    if (s.length() == 0) {
        return s;
    }

    size_t begin = s.find_first_not_of(" \a\b\f\n\r\t\v");
    size_t end = s.find_last_not_of(" \a\b\f\n\r\t\v");

    if (begin == string::npos) {
        return "";
    }

    return string(s, begin, end - begin + 1);
}

int main()
{
    string text = "  The find family of string member functions "
                  "locates a character or group of characters within a given string."
                  " Here are the members of the find family and their general usage :  \t";

    int pos = text.find("give");
    cout << pos << endl;
    pos = text.find_first_of("give", 20);
    cout << pos << endl;
    pos = text.find_last_of("give");
    cout << pos << endl;
    pos = text.find_first_not_of("The");
    cout << pos << endl;
    pos = text.rfind(":");
    cout << pos << endl;

    string s = trim(text);
    cout << s << endl;
    return 0;
}