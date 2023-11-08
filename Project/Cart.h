#ifndef CART_H_INCLUDED
#define CART_H_INCLUDED

#include <iostream>
#include <map>
#include <List>
#include "Product.h"
#include "Stock.h"

using namespace std;

class Cart
{
    friend class Store;
public:

    // Constructor and Destructor
    Cart();
    Cart(map<int, int>);
    ~Cart();
    // Constructor and Destructor

    // SETTER and GETTER
    void setItems(map<int, int>);
    map<int, int>& getItems();
    // SETTER and GETTER

    //
    float get_total_price(const list<Product>&) const;
    void add(int, int);
    void remove_item(int);
    void print(const list<Product> &) const;
    void check_out(Stock&);
    void reset();
    //

private:
    map<int, int> items;
};
#endif // CART_H_INCLUDED
