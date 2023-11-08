#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include "Cart.h"
#include "Store.h"
#include "Product.h"


using namespace std;

// Constructor and Destructor
Cart::Cart()
{

}
Cart::Cart( map<int, int> items)
{
    setItems(items);
}
Cart::~Cart()
{

}
// Constructor and Destructor


// SETTER and GETTER
void Cart::setItems(map<int, int> items)
{
    this->items = items;
}
map<int, int>& Cart::getItems()
{
    return items;
}
// SETTER and GETTER


//
float Cart::get_total_price(const list<Product> &lp) const
{
    float totalPrice = 0;

    for(auto it = items.begin(); it != items.end(); it++)
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

void Cart::add(int product_id, int quantity)
{
    items.insert(pair<int, int>(product_id, quantity));
    cout << endl << "added successfully done!" << endl;
}

void Cart::remove_item(int product_id)
{
    items.erase(product_id);
    cout << endl << "remove successfully done!" << endl;
}

void Cart::print(const list<Product> &lp) const
{
    cout << endl << "------------------------------------VIEW CART------------------------------------" << endl;

    bool check = false;

    for(auto it = items.begin(); it != items.end(); it++)
    {
        check = true;
        for(auto itList = lp.begin(); itList != lp.end(); itList++)
        {
            if(it->first == itList->getId())
            {
                cout << "product Id: " << left << setw(5) << itList->getId()
                     << "Name: " << left << setw(15) << itList->getName()
                     << "price: " << left << setw(10) << itList->getPrice()
                     << "Brand: " << left << setw(15) << itList->getBrand()
                     << "quantity: " << left << setw(7) << it->second
                     << "expire date: " << left << setw(12) << static_cast<string>(itList->getExpire_date()) << endl;
                break;
            }
        }
    }
    if(check == false)
        cout << "\nYour cart is empty!" << endl;
}

void Cart::check_out(Stock &stock)
{
    for(auto it = getItems().begin(); it != getItems().end(); it++)
    {
        stock.change_count_by(it->first, -(it->second));
    }
    cout << endl;
}

void Cart::reset()
{
    items.clear();
    cout << endl << "clear cart succussfully done!" << endl;
}
//
