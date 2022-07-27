#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

int main()
{
    vector<int> vInt(10, 0);
    vector<int> vInt1(10, 0);
    for (auto it = vInt.begin(); it != vInt.end(); it++) {
        *it = it - vInt.begin();
    }
    vInt1 = vInt;
    for (auto i : vInt1) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}