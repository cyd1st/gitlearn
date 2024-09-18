#include <iostream>

using namespace std;

void fun() 
{
    int a = 13;
    auto f = [a](const int b) {
        return a + b;
    };
    cout << f(6) << endl;
}
int main()
{
    fun();
    return 0;
}