#ifndef STOCK_H_INCLUDED
#define STOCK_H_INCLUDED

#include <iostream>
#include <map>

using namespace std;

class Stock
{
public:
    // Constructor and Destructor
    Stock();
    Stock(map<int, int>);
    ~Stock();
    // Constructor and Destructor

    // SETTER and GETTER
    void setItems(map<int, int>);
    map<int, int>& getItems();
    // SETTER and GETTER

    //
    void view_stock() const;
    int get_count(int);
    void change_count_by(int, int);
    //

private:
    map<int, int> items;
};


#endif // STOCK_H_INCLUDED
