#include <iostream>
using namespace std;

template <class T>
T Inc(T n)
{
    return 1 + n;
}

template <class T>
void Swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}
int main() 
{
    int a = 10, b = 9;
    Swap(a, b);

    double c = 3.14, d = 2.71;
    Swap(c, d);

    cout << a << " " << b << endl;
    cout << c << " " << d << endl;
    
    return 0;
}

