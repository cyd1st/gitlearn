#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::cin; using std::cout; using std::endl;

int main(void)
{
    string str;
    vector<string> paragraph;
    while (getline(cin, str)) {
        paragraph.push_back(str);
    }

    for (auto it = paragraph.begin(); it != paragraph.cend() && !it->empty(); ++it) {
        for (auto &c : *it) {
            c = toupper(c);
        }
        cout << *it << endl;
    }
    // cout << paragraph.size() << endl;
    return 0;
}