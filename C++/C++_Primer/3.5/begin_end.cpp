#include <iostream>

using std::begin;
using std::end;
using std::cout;
using std::endl;

int main()
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto be = begin(arr);
    auto en = end(arr);

    for (; be != en; be++) {
        cout << *be << " ";
    }
    cout << endl;;
}