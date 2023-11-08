#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_H_INCLUDED

#include <iostream>
#include <string>
#include "Date.h"

using namespace std;

class Product
{
public:
    // Constructor and Destructor
    Product(int, string, float, string, Date);
    Product();
    ~Product();
    // Constructor and Destructor

    // SETTER and GETTER
    void setId(int);
    int getId() const;

    void setName(string);
    string getName() const;

    void setPrice(float);
    float getPrice() const;

    void setBrand(string);
    string getBrand() const;

    void setExpire_date(Date);
    Date getExpire_date() const;
    // SETTER and GETTER

private:
    int id;
    string name;
    float price;
    string brand;
    Date expire_date;
};

#endif // PRODUCT_H_INCLUDED
