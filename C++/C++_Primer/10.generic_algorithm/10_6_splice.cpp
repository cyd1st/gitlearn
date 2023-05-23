#include <bits/c++config.h>
#include <iostream>
#include <iterator>
#include <list>
#include <forward_list>

using namespace std;

void flist_splice_after()
{
    forward_list<int> l = {5, 6};
    forward_list<int> l2 = {2, 3, 4};
    auto it = l.before_begin();
    l.splice_after(it, l2, ++begin(l2));
    for (auto i : l)
        cout << i << " ";
    cout << endl; //6 5
}
void flist_splice()
{
    forward_list<int> l = {5, 6};
    forward_list<int> l2 = {2, 3, 4};
    auto it = l.before_begin();
    l.splice_after(it, l2);
    for (auto i : l)
        cout << i << " ";
    cout << endl; //2 3 4 5 6
    cout << l2.empty() << endl; //1
}
void list_splice()
{
    list<int> l = {1, 5, 6};
    list<int> l2 = {2, 3, 4};
    auto it = ++l.begin();
    l.splice(it, l2);
    for (auto i : l)
        cout << i << " ";
    cout << endl; //1 2 3 4 5 6
    cout << l2.size() << endl; //0
}

int main()
{
    list_splice();
    flist_splice();
    flist_splice_after();
    return 0;
}