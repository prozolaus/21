#include "Chrono.h"

namespace Chrono
{
    Date::Date(int yy, Month mm, int dd)
        : y{yy}, m{mm}, d{dd}
    {
        if (!is_date(yy, mm, dd))
            throw Invalid{};
    }
    
    const Date &default_date()
    {
        static Date dd{1970, Month::jan, 1}; // The day zero - thursday
        return dd;
    }

    Date::Date()
        : y{default_date().year()},
          m{default_date().month()},
          d{default_date().day()}
    {
    }

    // secondary functions:
    bool is_date(int y, Month m, int d)
    {
        // if (y < zero.year())
        // return false;
        if (d <= 0)
            return false; // d must be positive
        if (m < Month::jan || m > Month::dec)
            return false;

        int days_in_month = 31; // no more than 31 days in a month
        switch (m)
        {
        case Month::feb:
            days_in_month = (leapyear(y)) ? 29 : 28;
            break;
        case Month::apr:
        case Month::jun:
        case Month::sep:
        case Month::nov:
            days_in_month = 30;
            break;
        }
        if (d > days_in_month)
            return false;
        return true;
    }

    // a leap year is disivible by 4, but not by 100, except if it is divisible by 400
    bool leapyear(int y)
    {
        if (y < 0)
            error("leapyear(): The year cannot be negative.");
        return y % 4 == 0 && y % 100 != 0 || y % 400 == 0;
    }

    bool operator==(const Date &a, const Date &b)
    {
        return a.year() == b.year() && a.month() == b.month() && a.day() == b.day();
    }

    bool operator!=(const Date &a, const Date &b)
    {
        return !(a == b);
    }

    ostream &operator<<(ostream &os, const Date &d)
    {
        return os << ((d.day() < 10) ? "0" : "") << d.day()
                  << '.' << ((int(d.month()) < 10) ? "0" : "") << int(d.month())
                  << '.' << d.year();
    }

    istream &operator>>(istream &is, Date &dd)
    {
        int y, m, d;
        char ch1, ch2;
        is >> d >> ch1 >> m >> ch2 >> y;
        if (!is)
            return is;
        if (ch1 != '.' || ch2 != '.' || !is_date(y, Month(m), d)) 
        {
            is.clear(ios_base::failbit); // set an error bit
            return is;
        }
        dd = Date(y, Month(m), d); // update dd
        return is;
    }
}