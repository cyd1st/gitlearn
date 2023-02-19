#include <iostream>

using namespace std;

class Complex {
    public:
        double real, imag;
        Complex() {}
        Complex(const Complex &c) {
            real = c.real;
            imag = c.imag;
            cout << "Copy Comstructor called";
        }
}
int main()
{
    Complex c1;
    Complex c2(c1);
    return 0;
}