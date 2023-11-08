#ifndef RECEIPT_H_INCLUDED
#define RECEIPT_H_INCLUDED

#include <iostream>
#include <map>
#include <list>
#include "Date.h"
#include "Product.h"

using namespace std;

class Receipt
{
    friend class Store;
public:

    // Constructor and Destructor
    Receipt();
    Receipt(map<int, int>, Date);
    ~Receipt();
    // Constructor and Destructor

    // SETTER and GETTER
    void setItems(map<int, int>);
    map<int, int>& getItems();

    void setDate(Date);
    Date getDate() const;
    // SETTER and GETTER

    //
    float get_total_price(const list<Product> &);
    //

private:
    map<int, int> items;
    Date date;
};
#endif // RECEIPT_H_INCLUDED
