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
    char dash;

    is >> d.month;
    is >> dash;
    if (dash != '-') {
        is.setstate(ios::failbit);
    }

    is >> d.day;
    is >> dash;
    if (dash != '-') {
        is.setstate(ios::failbit);
    }

    is >> d.year;
    return is;
}