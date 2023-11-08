#ifndef STORE_H_INCLUDED
#define STORE_H_INCLUDED

#include <iostream>
#include <list>
#include <map>

#include "Product.h"
#include "Customer.h"
#include "Stock.h"

using namespace std;

class Store
{
     //friend class Stock;
public:

    // Constructor and Destructor
    Store();
    Store(list<Product>, Stock, list<Customer>);
    ~Store();
    // Constructor and Destructor

    // SETTER and GETTER
    void setProducts(list<Product>);
    list<Product>& getProducts();

    void setStock(Stock);
    Stock& getStock();

    void setCustomers(list<Customer>);
    list<Customer>& getCustomers();
    // SETTER and GETTER

    //
    void check_out(int);
    void add_customer();
    void add_product();
    void view_product();
    void view_customer();
    void save_to_file();
    void seles_report(Date, Date); // is not correct!
    //

    // PUBLIC FUNCTION
    int find_product(int);
    bool find_customer(int);
    // PUBLIC FUNCTION

private:
    list<Product> products;
    Stock stock;
    list<Customer> customers;

};



#endif // STORE_H_INCLUDED
