#include <iostream>
using std::cin; using std::endl;

int main() {
    int i, j;
    cin >> i >> j;
    // cout << "i = " << i << std::endl;  // error:use of undeclared identifier 'cout'
    std::cout << "j = " << j << endl;

    return 0;
}