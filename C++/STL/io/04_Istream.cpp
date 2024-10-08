#include <cstring>
#include <iostream>

using namespace std;

int main()
{
    char buf[20];
    cin.get(buf, 20, ' ');
    cin.get(buf, 20, ' ');
    cout << strlen(buf) << endl;
}