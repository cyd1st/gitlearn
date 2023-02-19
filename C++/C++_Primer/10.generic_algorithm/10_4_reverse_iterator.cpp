#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <iterator>

using namespace std;

void _10_37()
{
    vector<int> ivec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    list<int> ilst;
    copy(ivec.crbegin() + 3, ivec.crbegin() + 8, back_inserter(ilst));
    // copy(ivec.crbegin() + 3, ivec.crbegin() + 8, ilst.begin());
    for (auto i : ilst)
        cout << i << " ";
    cout << endl;
}

void find_test()
{
    string s = "first,fsg,gdhgde,hfhfj,jfh,last";
    auto e = find(s.cbegin(), s.cend(), ',');
    cout << string(s.cbegin(), e) << endl;

    auto e2 = find(s.crbegin(), s.crend(), ',');
    cout << string(s.crbegin(), e2) << endl;
    cout << string(e2.base(), s.cend()) << endl;
}

void sort_it_test()
{
    vector<int> vi = {34, 46, 64, 7, 06, 24, 67, 8, 34};
    sort(vi.rbegin(), vi.rend());
    for (auto it = vi.begin(); it != vi.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

void begin_reverse_test()
{
    vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto it = vi.cend() - 1; it >= vi.cbegin(); --it) {
        cout << *it << " ";
    }
    cout << endl;
}

void rbegin_test()
{
    vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto it = vi.crbegin(); it != vi.crend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

int main()
{
    // rbegin_test();
    // begin_reverse_test();
    _10_37();
    // sort_it_test();
    // find_test();
    return 0;
}