#include <iostream>
#include <ctime>
#include "Customer.h"

using namespace std;

// Constructor and Destructor
Customer::Customer()
{

}

Customer::Customer(int id, string name, string phone_number, string address, float balance)
{
    setId(id);
    setName(name);
    setPhoneNumber(phone_number);
    setAddress(address);
    setBalance(balance);
}

Customer::~Customer()
{

}
// Constructor and Destructor


// SETTER and GETTER
void Customer::setId(int id)
{
    this->id = id;
}
int& Customer::getId()
{
    return id;
}

void Customer::setName(string name)
{
    this->name = name;
}
string Customer::getName() const
{
    return name;
}

void Customer::setPhoneNumber(string phone_number)
{
    this->phone_number = phone_number;
}
string Customer::getPhoneNumber() const
{
    return phone_number;
}

void Customer::setHistory(list<Receipt> history)
{
    this->history = history;
}
list<Receipt>& Customer::getHistory()
{
    return history;
}

void Customer::setAddress(string address)
{
    this->address = address;
}
string Customer::getAddress() const
{
    return address;
}

void Customer::setCart(Cart cart)
{
    this->cart = cart;
}
Cart& Customer::getCart()
{
    return cart;
}

void Customer::setBalance(float balance)
{
    this->balance = balance;
}
float &Customer::getBalance()
{
    return balance;
}
// SETTER and GETTER


//
void Customer::convert_cart_to_receipt(const list<Product> &lp)
{
    balance -= cart.get_total_price(lp);
    Receipt r;
    pair<int, int> item;
    Date d;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    d.setYear(1900 + ltm->tm_year);
    d.setMonth(1 + ltm->tm_mon);
    d.setDay(ltm->tm_mday);

    r.setDate(d);

    for(auto it = cart.getItems().begin(); it != cart.getItems().end(); it++)
    {
        item.first = it->first;
        item.second = it->second;
        r.getItems().insert(item);
    }
    history.push_back(r);
    cart.reset();
    cout << "convert cart to receipt is done successfully!" << endl;
}
float Customer::get_tatal_purchace_amount(const list<Product> &lp)
{
    float totale_price = 0;
    for(auto it = history.begin(); it != history.end(); it++)
    {
        totale_price += it->get_total_price(lp);
    }
    return totale_price;
}
//
