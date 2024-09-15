#include <iostream>

using namespace std;

class Complex {
	double m_real;
	double m_imag;
public:
	Complex(double real, double imag) : m_real(real), m_imag(imag) {}
	double real() const { return m_real;}
	double imag() const { return m_imag;}
	Complex operator+(const Complex& rhs) {
		return Complex(m_real + rhs.real(), m_imag + rhs.imag());
	}
	void print() {
		cout << m_real << '+' << m_imag << 'i' << endl; 
	}
};

int main()
{
	Complex a(1.0, 2.0);
	Complex b(2.1, 3.2);
	Complex c = a + b;
	c.print();
	return 0;
}
