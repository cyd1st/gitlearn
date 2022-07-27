#include <iostream>

using std::string;
using std::cin; using std::cout; using std::endl;

int main() {
    string line;
    string str;
    while (getline(cin, line)) {
        if (line.size()) {
            str += line;
        } else {
            break;
        }
    }
    cout << str << endl;
}