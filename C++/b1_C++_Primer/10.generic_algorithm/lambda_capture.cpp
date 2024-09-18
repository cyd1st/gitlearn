#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

int count_if_size_greater_6(vector<string> &words)
{
    return count_if(words.begin(), words.end(), [](const string& s) {
        return s.size() > 6;
    });
}

void lambda_ret_type()
{
    vector<int> v1 = {-3, -2, -1, 0, 1, 2, 3};
    transform(v1.cbegin(), v1.cend(), v1.begin(), [](int i) {
        if (i > 0) return i;
        else return -i;
    });
    for(auto i : v1) cout << i << " ";
    cout << endl;
}

void fun3()
{
    int i = 10;
    auto f = [i]() mutable { return ++i; };
    cout << i << endl;
    i = 1;
    cout << f() << endl;
}

void implict_reference(ostream &os, char sep)
{
    vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8};
    for_each(vi.begin(), vi.end(), [&, sep](const int a) {
        os << a << sep;
    });
    cout << "\b " << endl;
}

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
    implict_reference(cout, ',');
    fun3();
    lambda_ret_type();
    return 0;
}