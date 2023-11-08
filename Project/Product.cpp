#include <iostream>
#include "Product.h"

using namespace std;

// Constructor and Destructor
Product::Product(int id, string name, float price, string brand, Date expire_date)
{
    setId(id);
    setName(name);
    setPrice(price);
    setBrand(brand);
    setExpire_date(expire_date);
}

Product::Product()
{

}

Product::~Product()
{

}
// Constructor and Destructor


// SETTER and GETTER
void Product::setId(int id)
{
    this->id = id;
}
int Product::getId() const
{
    return id;
}

void Product::setName(string name)
{
    this->name = name;
}
string Product::getName() const
{
    return name;
}

void Product::setPrice(float price)
{
    this->price = price;
}
float Product::getPrice() const
{
    return price;
}

void Product::setBrand(string brand)
{
    this->brand = brand;
}
string Product::getBrand() const
{
    return brand;
}

void Product::setExpire_date(Date expire_date)
{
    this->expire_date = expire_date;
}
Date Product::getExpire_date() const
{
    return expire_date;
}
// SETTER and GETTER
