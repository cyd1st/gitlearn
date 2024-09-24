#ifndef _MY_DATE
#define _MY_DATE

#include <iosfwd>
#include <iomanip>
using namespace std;

class Date {
    int year;
    int month;
    int day;

public:
    Date() {}
    Date(const Date &d)
    {
        year = d.year;
        month = d.month;
        day = d.day;
    }
    Date(int y, int m, int d) : year(y), month(m), day(d) {}
    std::string getMonth() const { return std::to_string(month); }
    std::string getDay() const { return std::to_string(day); }
    std::string getYear() const { return std::to_string(year); }

    friend ostream &operator<<(ostream &os, const Date &d);

    friend istream &operator>>(istream &is, Date &d);
};

#endif