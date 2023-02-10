#include <iostream>
#include <vector>
#include <iterator>
#include <list>

using namespace std;

void print_vector(list<int> &vi)
{
    for (auto i : vi)
        cout << i << " ";
    cout << endl;
}

void copy()
{
    vector<int> vi = {1,2,3,4,5,6,7,8,9};
    list<int> l1, l2, l3;
    auto it1 = inserter(l1, l1.begin());
    auto it2 = back_inserter(l2);
    auto it3 = front_inserter(l3);

    copy(vi.begin(), vi.end(), it1);
    copy(vi.begin(), vi.end(), it2);
    copy(vi.begin(), vi.end(), it3);

    print_vector(l1);
    print_vector(l2);
    print_vector(l3);
}
int main()
{
    copy();
    return 0;
}