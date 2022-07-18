#include <iostream>

using std::cout;
using std::endl;

int main()
{
    constexpr size_t array_size = 10;
    int array[10] = {};
    int array1[10] = {};
    for (int i = 0; i < array_size; i++) {
        array[i] = i;
    }
    for (int i = 0; i < array_size; i++) {
        array1[i] = array[i];
    }
    for (auto i : array1) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}