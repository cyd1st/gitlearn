//: C04:DataLogger.cpp {O}
// Datapoint implementations.
#include "01_DataLogger.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

ostream &operator<<(ostream &os, const Coord &c)
{
    return os << c.deg << '*' << c.min << '\'' << c.sec << '"';
}

string Coord::toString() const
{
    ostringstream os;
    os << *this; // 调用 operator<<(ostream& os, const Coord& c) 重载
    return os.str();
}

ostream &operator<<(ostream &os, const DataPoint &d)
{
    os.setf(ios::fixed, ios::floatfield);
    char fillc = os.fill('0'); // Pad on left with '0'
    tm *tdata = localtime(&d.timestamp);
    // clang-format off
    os << setw(2) << tdata->tm_mon + 1 << '\\'
       << setw(2) << tdata->tm_mday << '\\'
       << setw(4) << tdata->tm_year + 1900 << ' '
       << setw(2) << tdata->tm_hour << ':'
       << setw(2) << tdata->tm_min << ':'
       << setw(2) << tdata->tm_sec;
    // clang-format on
    os.fill(' ');                      // Pad on left with ' '
    streamsize prec = os.precision(4); // 小数点后4位

    // clang-format off
    os << " Lat:"
       << setw(9) << d.latitude.toString() << ", Long:"
       << setw(9) << d.longitude.toString() << ", depth:"
       << setw(9) << d.depth << ", temp:"
       << setw(9) << d.temperature;
    // clang-format on
    os.fill(fillc);
    os.precision(prec);
    return os;
} ///:~