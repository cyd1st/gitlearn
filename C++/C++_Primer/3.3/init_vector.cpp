#include <vector>
#include <iostream>

using std::vector;
using std::string;
using std::cin; using std::cout; using std::endl;

int main() {
    // init 
    vector<int> vInt(11, 22);
    vector<string> vStr(10, "hi");

    vector<int> vInt2 = {11, 12, 13, 14};
    vector<string> vStr2{10, "hi"}; // equal to vector<string> vStr(10, "hi");
    vector<string> vStr3{10}; // equal to vector<string> vStr3(10);

    vector<vector<int>> vVec;
    
    // push back
    vector<int> vInt3;
    for (int i = 0; i < 100; i++) {
        vInt3.push_back(i);
    }

    string word;
    vector<string> vWords;
    while (cin >> word) {
        vWords.push_back(word);
    }

    string str1;
    vector<string> vStrs;
    while (getline(cin, str1)) {
        vStrs.push_back(str1);
    }

    // get element
    for (auto &i : vInt3) {
        i *= i;
    }

    for (auto i : vInt3) {
        cout << i << " ";
    }
    cout << endl;

    cout << "end" << endl;

    return 0;
}