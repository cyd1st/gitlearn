#include <iostream>

int main()
{
    int i = 42, *p = &i, &r = i;

    decltype(i) a;     // i is an int, so a is an int
    decltype((i)) b = i; // (i) is an lvalue, so b is an int&
    decltype(i + 1) c;   // i + 1 is an expression, so c is an int
    decltype(&i) d; // &i is an expression, so d is an int*

}