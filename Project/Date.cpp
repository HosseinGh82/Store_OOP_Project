#include <iostream>
#include "Date.h"
#include <stdexcept>
#include <iomanip>
using namespace std;

const unsigned int Date::daysPerMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Constructor and Destructor
Date::Date(unsigned int y, unsigned int m, unsigned int d)
{
    setYear(y);
    setMonth(m);
    setDay(d);
}

Date::Date(const Date &dateToCopy)
{
    setYear(dateToCopy.getYear());
    setMonth(dateToCopy.getMonth());
    setDay(dateToCopy.getDay());
}

Date::Date(int intDate)
{
    int d = intDate % 100;
    intDate /= 100;
    int m = intDate % 100;
    int y = intDate / 100;
    setYear(y);
    setMonth(m);
    setDay(d);
}

Date::Date(string str)
{
    string year = str.substr(0, 4);
    string month = str.substr(5, 2);
    string day = str.substr(8, 2);

    setYear(stoi(year));
    setMonth(stoi(month));
    setDay(stoi(day));

}
// Constructor and Destructor


// SETTER and GETTER
void Date::setYear(unsigned int y)
{
    year = y;
}

unsigned int Date::getYear() const
{
    return year;
}

void Date::setMonth(unsigned int m)
{
    if(m >= 1 && m <= 12)
        month = m;
    else
        throw std::invalid_argument("Invalid month!");
}

unsigned int Date::getMonth() const
{
    return month;
}

void Date::setDay(unsigned int d)
{
    if(checkDay(d))
        day = d;
    else
        throw std::invalid_argument("Invalid day for current month and year!");
}

unsigned int Date::getDay() const
{
    return day;
}

Date::~Date()
{

}
// SETTER and GETTER


// PUBLIC FUNCTION
bool Date::leap(unsigned int testYear)
{
    if (testYear % 400 == 0 ||
       (testYear % 4 == 0 && testYear % 100 != 0))
       return true;
    else
        return false;
}

bool Date::endOfMonth(unsigned int testDay)
{
    if(leap(year) && month == 2)
        return testDay == 29;
    else
        return testDay == Date::daysPerMonth[month];
}
// PUBLIC FUNCTION


// PRIVATE FUNCTION
bool Date::checkDay(unsigned int testDay) const
{

    if(testDay <= daysPerMonth[month])
        return true;
    if((month == 2 && testDay == 29) &&
       (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)))
        return true;
    return false;
}

void Date::increament()
{
    if(!endOfMonth(day))
        ++day;
    else if(month != 12)
    {
        ++month;
        day = 1;
    }
    else
    {
        ++year;
        month = day = 1;
    }
}
// PRIVATE FUNCTION


// OPERATOR IN CLASS
Date &Date::operator++()
{
    increament();
    return *this;
}

Date Date::operator++(int)
{
    Date t = *this;
    increament();
    return t;
}


bool Date::operator<=(Date date)
{
    string left = *this;
    string right = date;
    if(left <= right)
        return true;
    else
        return false;
}

bool Date::operator==(Date date)
{
    if(this->getYear() == date.getYear() && this->getMonth() == date.getMonth() && this->getDay() == date.getDay())
        return true;
    return false;
}

Date::operator string() const
{
    string s;
    s = to_string(getYear()) + "/" + to_string(getMonth()) + "/" + to_string(getDay());
    return s;
}
// OPERATOR IN CLASS


// OPERATOR OUT OF CLASS
ostream &operator<<(ostream &output, const Date &date)
{
    output << setfill('0') << setw(4) << date.getYear() << "." << setw(2) << date.getMonth() << "." << setw(2) << date.getDay();
    return output;
}

istream& operator>>(istream &input, Date &date)
{
    input >> setw(4) >> date.year;
    input.ignore();
    input >> setw(2) >> date.month;
    input.ignore();
    input >> setw(2) >> date.day;

    return input;
}
// OPERATOR OUT OF CLASS


