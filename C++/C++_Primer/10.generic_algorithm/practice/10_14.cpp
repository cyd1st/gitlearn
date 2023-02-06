#include <iostream>

using namespace std;

int main()
{
    auto ld_add = [](const int a, const int b) {
        return a + b;
    };
    cout << ld_add(3, 2) << endl;
    return 0;
}