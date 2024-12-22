#include <iostream>

template <class T>
void Swap(T &x, T &y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

int main()
{
    int a = 10, b = 1;
    Swap(a, b);
    std::cout << a << " " << b << std::endl;

    double c = 12.45, d = 20.45;
    Swap(c, d);
    std::cout << c << " " << d << std::endl;

    return 0;
}