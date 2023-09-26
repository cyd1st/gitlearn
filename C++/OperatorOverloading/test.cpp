/* ************************************************************************
> File Name:     test.cpp
> Author:        cyD
> Created Time:  Sun Jul  2 00:39:43 2023
> Description:   
 ************************************************************************/

#include <iostream>

using namespace std;

class Complex
{
public:
    double real, imag;
    Complex(double r=0.0, double i=0.0) : real(r), imag(i) {
};
    Complex operator-(const Complex &a);
};

Complex operator+(const Complex &a, const Complex &b)
{
    return Complex(a.real+b.real, a.imag+b.imag);
}

Complex Complex::operator-(const Complex &c)
{
    return Complex(real-c.real, imag-c.imag);
}

int main()
{
    Complex a(12, 34.2), b(1.34, 34), c;
    c = a + b;
    cout << "c = " << c.real << "+" << c.imag << endl;
    c = a - b;
    cout << "c = " << c.real << "+" << c.imag << endl;
    return 0;
}
