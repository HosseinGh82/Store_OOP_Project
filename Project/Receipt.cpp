#include <iostream>
#include "Receipt.h"
#include "Store.h"

using namespace std;

// Constructor and Destructor
Receipt::Receipt()
{

}
Receipt::Receipt(map<int, int> items, Date date)
{
    setItems(items);
    setDate(date);
}
Receipt::~Receipt()
{

}
// Constructor and Destructor


// SETTER and GETTER
void Receipt::setItems(map<int, int> items)
{
    this->items = items;
}
map<int, int>& Receipt::getItems()
{
    return items;
}

void Receipt::setDate(Date date)
{
    this->date = date;
}
Date Receipt::getDate() const
{
    return date;
}
// SETTER and GETTER


//
float Receipt::get_total_price(const list<Product> &lp)
{
    float totalPrice = 0;

    int i = 0;
    for(auto it = getItems().begin(); it != getItems().end(); it++)
    {
        for(auto itList = lp.begin(); itList != lp.end(); itList++)
        {
            if(it->first == itList->getId())
            {
                totalPrice += it->second * itList->getPrice();
                break;
            }
        }
    }
    return totalPrice;
}
//

