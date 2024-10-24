#include <iostream>

using namespace std;

inline ostream &nl(ostream &os) { return os << '\n'; }

int main()
{
    cout << "123" << nl << "456";
    return 0;
}