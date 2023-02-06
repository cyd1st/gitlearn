#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

void reference_cout(ostream &os = cout, char sep = ' ')
{
    vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8};
    for_each(vi.cbegin(), vi.cend(), [&os, sep](const int a) {
        os << a << sep;
    });
    os << "\b " << endl; // remove the last sep
}

void reference_passing()
{
    int v = 20;
    auto f = [&v] { return v; };
    v = 30;
    cout << f() << endl; // 30
}

void func()
{
    int v = 20;
    auto f = [v] { return v; };
    v = 30;
    cout << f() << endl; // 20
}
int main()
{
    func();
    reference_passing();
    reference_cout(cout, ',');
    return 0;
}