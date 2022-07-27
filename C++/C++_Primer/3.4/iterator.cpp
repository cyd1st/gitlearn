#include <iostream>

using std::string;
using std::cin; using std::cout; using std::endl;

int main(void) {
    string str;
    getline(cin, str);
    if (str.begin() != str.end()) {
        auto c = str.begin();
        *c = toupper(*c);
    }
    cout << str << endl;

    getline(cin, str);
    for (auto it = str.begin(); it != str.end() && !isspace(*it); ++it) {
        *it = toupper(*it);
    }
    cout << str << endl;
    return 0;
}