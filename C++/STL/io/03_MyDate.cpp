#include "03_MyDate.h"

ostream &operator<<(ostream &os, const Date &d)
{
    char fillc = os.fill('0');
    os << setw(2) << d.getMonth() << '-' << setw(2) << d.getDay() << '-' << setfill(fillc)
       << d.getYear();
    return os;
}

istream &operator>>(istream &is, Date &d)
{
    int year, month, day;
    is >> month;
    char dash;
    is >> dash;
    if (dash != '-') {
        is.setstate(ios::failbit);
    }
    is >> day;
    is >> dash;
    if (dash != '-') {
        is.setstate(ios::failbit);
    }
    is >> year;

    d = Date(year, month, day);
    return is;
}