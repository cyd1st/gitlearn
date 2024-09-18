#include <iostream>
#include <vector>

using std::vector;
using std::cin; using std::cout; using std::endl;

int main(void)
{
    vector<int> vInt;
    for (int i = 0; i < 10; i++) {
        vInt.push_back(i);
    }

    if (vInt.empty()) {
        cout << "vInt empty." << endl;
    } else {
        cout << "vInt size is " << vInt.size() << "." << endl;
    }
    return 0;
}