#include <iostream>
#include <vector>

using std::vector;
using std::string;
using std::cin; using std::cout; using std::endl;

int main(void) {
    vector<int> vI1(10, 42);
    vector<int> vI2{42, 42, 42, 42, 42, 42, 42, 42, 42, 42};
    vector<int> vI3;
    for (int i = 0; i < 10; i++) {
        vI3.push_back(42);
    }
    if (vI1 == vI2 && vI2 == vI3) {
        cout << "success." << endl;
    }
    return 0;
}