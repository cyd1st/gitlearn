#include <iostream>
#include <vector>

using std::vector;
using std::string;
using std::cin; using std::cout; using std::endl;

int main(void) {
    string word;
    vector<string> vStr;
    while (cin >> word) {
        for (auto &c : word) {
            c = toupper(c);
        }
        vStr.push_back(word);
    }
    for (auto str : vStr) {
        cout << str << endl;
    }

    return 0;
}