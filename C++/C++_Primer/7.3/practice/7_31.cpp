#include <iostream>

class X;
class Y;

class X {
    Y *point; 
};

class Y {
    X *point;
};

int main()
{
    X x;
    Y y;
    return 0;
}