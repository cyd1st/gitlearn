#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>

using namespace std;

void practice_10_6()
{
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    fill_n(begin(a), sizeof(a)/sizeof(a[0]), 0);
    for (auto i : a) {
        cout << i << " ";
    }
    cout << endl;
}
void practice_10_7_a()
{
    vector<int> vec;
    list<int> lst;
    int i;
    while (cin >> i) // input ctrl + d to stop
        lst.push_back(i);
    copy(lst.begin(), lst.end(), back_inserter(vec));
    for (auto i : vec)
        cout << i << " ";
    cout << endl;
}
void practice_10_7_b()
{
    vector<int> vec;
    vec.reserve(10);
    fill_n(vec.begin(), 10, 0); // runtime error
}
int main()
{
    practice_10_6();
    practice_10_7_a();
    practice_10_7_b();
    return 0;
}