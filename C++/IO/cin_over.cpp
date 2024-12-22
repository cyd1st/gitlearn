#include <iostream>

using namespace std;

int main()
{
    int i;
    while (cin >> i) {
        cout << "out:\t" << i << endl;
    }

    // Pressing ctrl+d triggers EOF
    cout << "cin.eof() = " << cin.eof() << endl;
    // failbit set by invalid input(include EOF (Ctrl+D)).
    cout << "cin.fail() = " << cin.fail() << endl;
    
    return 0;
}