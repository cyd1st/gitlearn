#include <iostream>
using std::cout;
using std::endl;

int main()
{
    int ia[] = {0, 1, 2, 3, 4, 5};
    auto ib(ia);
    // ia = 3; // error, is is integer point.
    cout << ib[3] << endl;  // 3
}