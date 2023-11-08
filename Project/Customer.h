#ifndef CUSTOMER_H_INCLUDED
#define CUSTOMER_H_INCLUDED

#include <iostream>
#include <string>
#include <list>
#include "Cart.h"
#include "Receipt.h"

using namespace std;

class Customer
{
public:

    // Constructor and Destructor
    Customer();
    Customer(int , string , string, string, float);
    ~Customer();
    // Constructor and Destructor

    // SETTER and GETTER
    void setId(int);
    int& getId();

    void setName(string);
    string getName() const;

    void setPhoneNumber(string);
    string getPhoneNumber() const;

    void setHistory(list<Receipt>);
    list<Receipt>& getHistory();

    void setAddress(string);
    string getAddress() const;

    void setCart(Cart);
    Cart& getCart();

    void setBalance(float);
    float &getBalance();
    // SETTER and GETTER

    //
    void convert_cart_to_receipt(const list<Product> &);
    float get_tatal_purchace_amount(const list<Product> &);
    //

private:
    int id;
    string name;
    string phone_number;
    list<Receipt> history;
    string address;
    Cart cart;
    float balance;
};
#endif // CUSTOMER_H_INCLUDED
