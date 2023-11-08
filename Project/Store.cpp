#include <iostream>
#include <fstream>
#include <iomanip>
#include "Store.h"
#include "Customer.h"
#include <list>
#include <map>
#include <utility>

using namespace std;

// Constructor and Destructor
Store::Store()
{

}
Store::Store(list<Product> products, Stock stock, list<Customer> customers)
{
    setProducts(products);
    setStock(stock);
    setCustomers(customers);
}
Store::~Store()
{

}
// Constructor and Destructor


// SETTER and GETTER
void Store::setProducts(list<Product> products)
{
    this->products = products;
}
list<Product>& Store::getProducts()
{
    return products;
}

void Store::setStock(Stock stock)
{
    this->stock = stock;
}
Stock& Store::getStock()
{
    return stock;
}

void Store::setCustomers(list<Customer> customers)
{
    this->customers = customers;
}
list<Customer>& Store::getCustomers()
{
    return customers;
}
// SETTER and GETTER


//
void Store::check_out(int customer_id)
{
    cout << endl;
    cout << "-----------------------------CHECK OUT-----------------------------" << endl;
    cout << "customer Id:";
    cin >> customer_id;

    if(!find_customer(customer_id))
        throw invalid_argument("Customer id is wrong!");
    for(auto it = customers.begin(); it != customers.end(); it++)
    {
        if(it->getId() == customer_id)
        {
            if(it->getBalance() < it->getCart().get_total_price(getProducts()))
                throw invalid_argument("your balance is not enough!");
            it->getCart().check_out(stock);
            it->convert_cart_to_receipt(products);
            break;
        }
    }
}

void Store::add_customer()
{
    int id;
    string name;
    string phone_number;
    string address;
    float balance;

    cout << endl;
    cout << "------------------------------ADD CUSTOMER------------------------------" << endl;
    cout << "-ID: ";
    cin >> id;
    for(auto it = customers.begin(); it != customers.end(); it++)
    {
        if(it->getId() == id)
        {
            throw invalid_argument("This customer ID is exist!");
        }
    }
    cout << "-Name: ";
    cin >> name;
    cout << "-Phone Number: ";
    cin >> phone_number;
    cout << "-Address: ";
    cin >> address;
    cout << "-Balance: ";
    cin >> balance;

    Customer customer(id, name, phone_number, address, balance);
    customers.push_back(customer);

    cout << endl;
    cout << name << " is added successfully in customers list!" << endl;
}

void Store::add_product()
{
    int id;
    string name;
    float price;
    string brand;
    string expire_date;
    int quantity;

    cout << endl;
    cout << "------------------------------ADD PRODUCT------------------------------" << endl;
    cout << "-ID: ";
    cin >> id;
    for(auto it = products.begin(); it != products.end(); it++)
    {
        if(it->getId() == id)
        {
            throw invalid_argument("This product ID is exist!");
        }
    }
    cout << "-Name: ";
    cin >> name;
    cout << "-Price: ";
    cin >> price;
    cout << "-Brand: ";
    cin >> brand;
    cout << "-Expire date(EX: yyyy/mm/dd): ";
    cin >> expire_date;
    cout << "-In stock: ";
    cin >> quantity;


    pair<int, int> item(id, quantity);
    stock.getItems().insert(item);


    Product product(id, name, price, brand, expire_date);
    products.push_back(product);

    cout << endl;
    cout << name << " is added successfully in products list!" << endl;
}

void Store::view_product()
{
    cout << endl;
    cout << "------------------------------VIEW PRODUCT------------------------------" << endl;
    for(auto it = products.begin(); it != products.end(); it++)
    {
        for(auto itStock = stock.getItems().begin(); itStock != stock.getItems().end(); itStock++)
        {
            if(itStock->first == it->getId() && itStock->second > 0)
            {
                cout << "product Id: " << left << setw(5) << it->getId()
                     << "Name: " << left << setw(15) << it->getName()
                     << "price: " << left << setw(10) << it->getPrice()
                     << "Brand: " << left << setw(15) << it->getBrand()
                     << "quantity: " << left << setw(7) << itStock->second
                     << "expire date: " << left << setw(12) << static_cast<string>(it->getExpire_date()) << endl;
                break;
            }
        }
    }
}

void Store::view_customer()
{
    cout << endl;
    cout << "------------------------------VIEW CUSTOMER------------------------------" << endl;
    for(auto it = customers.begin(); it != customers.end(); it++)
    {
        cout << "Customer Id: " << left << setw(5) << it->getId()
                << "Name: " << left << setw(15) << it->getName()
                << "Phone number: " << left << setw(15) << it->getPhoneNumber()
                << "Address: " << left << setw(20) << it->getAddress()
                << "Balance: " << left << setw(10) << it->getBalance() << endl;
    }
}

void Store::save_to_file()
{
    ofstream productFile("product.txt");

    if(!productFile)
        throw invalid_argument("product.txt is not open!");
    for(auto it = products.begin(); it != products.end(); it++)
    {
        productFile << it->getId() << endl;
        productFile << it->getName() << endl;
        productFile << it->getPrice() << endl;
        productFile << it->getBrand() << endl;
        productFile << it->getExpire_date() << endl;
    }
    productFile.close();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ofstream customerFile("customer.txt");
    ofstream cartFile("cart.txt");
    ofstream receiptFile("receipt.txt");

    if(!customerFile)
        throw invalid_argument("customer.txt is not open!");
    if(!cartFile)
        throw invalid_argument("cart.txt is not open!");
    if(!receiptFile)
        throw invalid_argument("receipt.txt is not open!");

    for(auto it = customers.begin(); it != customers.end(); it++)
    {
        customerFile << it->getId() << endl;
        customerFile << it->getName() << endl;
        customerFile << it->getPhoneNumber() << endl;
        customerFile << it->getAddress() << endl;
        customerFile << it->getBalance() << endl;

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        cartFile << it->getId() << endl;
        cartFile << it->getCart().getItems().size() << endl;

        for(auto itCart = it->getCart().getItems().begin(); itCart != it->getCart().getItems().end(); itCart++)
        {
            cartFile << itCart->first << endl;
            cartFile << itCart->second << endl;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //string date;
        receiptFile << it->getId() << endl;
        receiptFile << it->getHistory().size() << endl;
        for(auto itReceipt = it->getHistory().begin(); itReceipt != it->getHistory().end(); itReceipt++)
        {
            receiptFile << itReceipt->getItems().size() << endl;
            for(auto itItems = itReceipt->getItems().begin(); itItems != itReceipt->getItems().end(); itItems++)
            {
                receiptFile << itItems->first << endl;
                receiptFile << itItems->second << endl;
            }
            receiptFile << itReceipt->getDate() << endl;
        }

    }
    customerFile.close();
    cartFile.close();
    receiptFile.close();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ofstream stockFile("stock.txt");
    if(!stockFile)
        throw invalid_argument("stock.txt is not open!");
    for(auto it = stock.getItems().begin(); it != stock.getItems().end(); it++)
    {
        stockFile << it->first << endl;
        stockFile << it->second << endl;
    }
    stockFile.close();

    cout << endl;
    cout << "save to file is done!" << endl;
}
void Store::seles_report(Date start, Date end)
{
    float total_buy_of_day= 0;
    float total_buy = 0;
    float best_buy = 0;
    Date best_day;
    for(Date d = start; d <= end; d++)
    {
        total_buy_of_day = 0;
        cout << d << ": ";
        for(auto it = getCustomers().begin(); it != getCustomers().end(); it++)
        {
            for(auto itHistory = it->getHistory().begin(); itHistory != it->getHistory().end(); itHistory++)
            {
                if(d == itHistory->getDate())
                {
                    total_buy_of_day += itHistory->get_total_price(products);
                }
            }
            if(total_buy_of_day > best_buy)
            {
                best_day = d;
                best_buy = total_buy_of_day;
            }
        }
        total_buy += total_buy_of_day;

        for(int i = 1; i < (total_buy_of_day / 100); i++)
                cout << "++ ";
        cout << endl;
    }

    cout << endl;
    cout << "best day: " << best_day << endl;
    cout << "total income: " << total_buy << endl;
}
//

// PUBLIC FUNCTION
int Store::find_product(int product_id)
{
    for(auto it = products.begin(); it != products.end(); it++)
    {
        if(product_id == it->getId())
            {
                for(auto itStock = getStock().getItems().begin(); itStock != getStock().getItems().end(); itStock++)
                    if(product_id == itStock->first)
                        return itStock->second;
            }
    }
    return -1;
}

bool Store::find_customer(int customer_id)
{
    for(auto it = customers.begin(); it != customers.end(); it++)
    {
        if(customer_id == it->getId())
            return true;
    }
    return false;
}
// PUBLIC FUNCTION

