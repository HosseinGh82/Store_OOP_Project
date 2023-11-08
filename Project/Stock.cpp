#include <iostream>
#include <map>
#include <iomanip>
#include "Stock.h"

using namespace std;

// Constructor and Destructor
Stock::Stock()
{

}
Stock::Stock(map<int, int> items)
{
    setItems(items);
}
Stock::~Stock()
{

}
// Constructor and Destructor


// SETTER and GETTER
void Stock::setItems(map<int, int> items)
{
    this->items = items;
}
map<int, int>& Stock::getItems()
{
    return items;
}
// SETTER and GETTER


//
void Stock::view_stock() const
{
    cout << endl << "------------------------------VIEW STOCK------------------------------" << endl;
    for(auto it = items.begin(); it != items.end(); it++)
    {
        cout << "product id: " << left << setw(5) << it->first << "quantity: " << left << setw(7) << it->second << endl;
    }
}

int Stock::get_count(int product_id)
{
    for(auto it = items.begin(); it != items.end(); it++)
    {
        if(it->first == product_id)
            return it->second;
    }
    return -1;
}

void Stock::change_count_by(int product_id, int count)
{
    for(auto it = items.begin(); it != items.end(); it++)
    {
        if(it->first == product_id)
        {
            it->second += count;
            break;
        }
    }
    cout << endl << "change count of product is done correctly!" << endl;
}
//
