#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <iostream>

using namespace std;

class Date
{
    friend ostream& operator<<(ostream&, const Date&);
    friend istream& operator>>(istream&, Date&);
public:
    // Constructor and Destructor
    explicit Date(unsigned int = 1900, unsigned int = 1, unsigned int = 1);
    Date(const Date&);
    Date(int);
    Date(string);
    ~Date();
    // Constructor and Destructor

    static const unsigned int daysPerMonth[13];

    // SETTER and GETTER
    void setYear(unsigned int);
    unsigned int getYear() const;
    void setMonth(unsigned int);
    unsigned int getMonth() const;
    void setDay(unsigned int);
    unsigned int getDay() const;
    // SETTER and GETTER


    // PUBLIC FUNCTION
    static bool leap(unsigned int);
    bool endOfMonth(unsigned int);
    // PUBLIC FUNCTION


    // OPERATOR IN CLASS
    Date &operator++();
    Date operator++(int);
    bool operator<=(Date);
    bool operator==(Date);
    operator std::string() const;
    // OPERATOR IN CLASS

private:
    unsigned int year;
    unsigned int month;
    unsigned int day;

    // PRIVATE FUNCTION
    void increament();
    bool checkDay(unsigned int) const;
    // PRIVATE FUNCTION
};

// OPERATOR OUT OF CLASS
istream& operator>>(istream&, Date&);
ostream &operator<<(ostream&, const Date&);
// OPERATOR OUT OF CLASS

#endif // DATE_H_INCLUDED
