#include <iostream>

using std::string;
using std::cout; using std::cin;
using std::endl;

void cmp1(string str1, string str2) {
    if (str1 == str2) {
        cout << "true" << endl;
    } else if (str1 > str2) {
        cout << str1 << endl;
    } else {
        cout << str2 << endl;
    }
}

void cmp2(string str1, string str2) {
    if (str1.size() == str2.size()) {
        cout << str1.size() << endl;
    } else if (str1.size() > str2.size()) {
        cout << str1 << endl;
    } else {
        cout << str2 << endl;
    }
}

int main () {
    string str1;
    string str2;
    cin >> str1;
    cin >> str2;
    cmp1(str1, str2);
    cmp2(str1, str2);

    return 0;
}