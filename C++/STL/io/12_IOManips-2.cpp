//: C04:InputWidth.cpp
// Shows limitations of setw with input.
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
using namespace std;

int main()
{
    istringstream is("one 2.34 five");
    string temp;
    is >> setw(2) >> temp;
    assert(temp == "on");
    std::cout << temp << std::endl; // on

    is >> setw(2) >> temp;
    assert(temp == "e");
    std::cout << temp << std::endl; // e

    double x;
    is >> setw(2) >> x;
    double relerr = fabs(x - 2.34) / x;
    std::cout << x << std::endl; // 2.34
    std::cout << relerr << std::endl; // 0
    assert(relerr <= numeric_limits<double>::epsilon());
} ///:~

