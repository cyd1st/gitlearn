/* ************************************************************************
> File Name:     10_4_inserter.cpp
> Author:        cyD
> Created Time:  Fri Feb 10 01:49:06 2023
> Description:   
 ************************************************************************/

#include <iostream>
#include <vector>
#include <iterator>
#include <list>
#include <forward_list>
#include <typeinfo>

using namespace std;

void forward_list_test()
{
    vector<int> l1 = {1, 2, 3, 4, 5};
    auto it = front_inserter(l1);
    it = 789;
    for (auto i : l1)
        cout << i << " ";
    cout << endl;
}
void inserter_test_2()
{
    list<int> l1 = {1, 2, 3, 4, 5};
    list<int> l2, l3;

    copy(l1.begin(), l1.end(), front_inserter(l2));
    for (auto i : l2) cout << i << " ";
    cout << endl; // 5 4 3 2 1

    copy(l1.begin(), l1.end(), inserter(l3, l3.begin()));
    for (auto i : l3) cout << i << " ";
    cout << endl; // 1 2 3 4 5
}

void front_inserter_test()
{
    list<int> l = {1, 2, 3, 4, 5};
    auto it = front_inserter(l);
    // equal to: front_insert_iterator<list<int> it = front_inserter(l);
    it = 789;
    for (auto i : l)
        cout << i << " ";
    cout << endl; // 789 1 2 3 4 5
}

void back_inserter_test()
{
    list<int> l = {1, 2, 3, 4, 5};
    auto it = back_inserter(l);
    it = 789; // equal to: *it = 789
    cout << typeid(it).name() << endl;
    // St20back_insert_iteratorINSt7__cxx114listIiSaIiEEEE
    cout << typeid(*it).name() << endl;
    // St20back_insert_iteratorINSt7__cxx114listIiSaIiEEEE
    for (auto i : l)
        cout << i << " ";
    cout << endl;
    // 1 2 3 4 5 789
}
void inserter_test()
{
    list<int> l = {1, 2, 3, 4, 5};
    for (auto it = l.begin(); it != l.end(); ++it) {
        if (*it == 3) {
            auto insert_it = inserter(l, it);
            insert_it = 789; // equal to *insert_it = 789
            insert_it++;
            *insert_it = 987;
            break;
        }
    }
    for (auto i : l)
        cout << i << " ";
    cout << endl;
}

void inserter_back_test()
{
    list<int> l = {1, 2, 3, 4, 5};
    auto it = inserter(l, l.end());
    *it = 789; // equal to it = 789
    for (auto i : l)
        cout << i << " ";
    cout << endl; // 1 2 3 4 5 789 
}

void inserter_front_test()
{
    list<int> l = {1, 2, 3, 4, 5};
    auto it = inserter(l, l.begin());
    *it = 789; // equal to it = 789
    for (auto i : l)
        cout << i << " ";
    cout << endl; // 789 1 2 3 4 5
}
int main()
{
    back_inserter_test();
    cout << "------------------" << endl;
    front_inserter_test();
    cout << "------------------" << endl;
    inserter_front_test();
    cout << "------------------" << endl;
    inserter_back_test();
    cout << "------------------" << endl;
    inserter_test();
    cout << "------------------" << endl;
    inserter_test_2();
    cout << "------------------" << endl;
    forward_list_test();
    
    // inserter_test();
    // inserter_test_2();
    return 0;
}
