#include <iostream>
#include <fstream>
#include <map>
#include "Store.h"
#include "Date.h"
#include "Cart.h"
#include "Product.h"
#include "Receipt.h"

using namespace std;

void load_file(Store&);
void home_page(Store&);
void customer_page(Store&);
void stock_page(Store&);

int main()
{
    int store_choose;
    Store store;
    try
    {
        load_file(store);
        home_page(store);
    }
    catch(invalid_argument &err)
    {
        cout << endl << err.what() << endl;
    }

    while(cin >> store_choose)
    {
        try
        {
            if(store_choose == 1)
                store.add_product();

            if(store_choose == 2)
                store.add_customer();

            if(store_choose == 3)
                store.view_product();

            if(store_choose == 4)
                store.view_customer();

            if(store_choose == 5)
                store.check_out(1);

            if(store_choose == 6)
            {
                cout << endl << "------------------------------------SALES REPORT------------------------------------" << endl;
                Date start, end;
                cout << "start: ";
                cin >> start;
                cout << "end: ";
                cin >> end;
                cout << endl;

                store.seles_report(start, end);
            }

            if(store_choose == 7)
            {
                int customer_id;
                int customer_choose;
                customer_page(store);
                while(cin >> customer_choose)
                {
                    if(customer_choose == 8)
                        break;

                    cout << "customer id: ";
                    cin >> customer_id;
                    if(!store.find_customer(customer_id))
                        throw invalid_argument("Customer id is wrong!");

                    auto it = store.getCustomers().begin();
                    for(it = store.getCustomers().begin(); it != store.getCustomers().end(); it++)
                        if(customer_id == it->getId())
                            break;

                    if(customer_choose == 1)
                    {
                        int product_id;
                        int quantity;
                        cout << endl;
                        cout << "------------------------------------ADD CART------------------------------------" << endl;
                        cout << "product id: ";
                        cin >> product_id;

                        if(store.find_product(product_id) == -1)
                            throw invalid_argument("Product id is wrong!");

                        cout << "quantity of product: ";
                        cin >> quantity;

                        if(store.find_product(product_id) < quantity)
                            throw invalid_argument("There is not enough product in stock!");

                        for(auto itItems = it->getCart().getItems().begin(); itItems != it->getCart().getItems().end(); itItems++)
                            if(itItems->first == product_id)
                                it->getCart().remove_item(product_id);

                        it->getCart().add(product_id, quantity);
                    }

                    if(customer_choose == 2)
                    {
                        int product_id;
                        cout << endl;
                        cout << "------------------------------------REMOVE ITEM------------------------------------" << endl;
                        cout << "product id: ";
                        cin >> product_id;

                        if(store.find_product(product_id) == -1)
                            throw invalid_argument("Product id is wrong!");

                        bool check = false;
                        for(auto itItems = it->getCart().getItems().begin(); itItems != it->getCart().getItems().end(); itItems++)
                            if(itItems->first == product_id)
                                check = true;
                        if(check == false)
                            throw invalid_argument("this product is not in your cart!");

                        it->getCart().remove_item(product_id);
                    }

                    if(customer_choose == 3)
                        it->getCart().print(store.getProducts());

                    if(customer_choose == 4)
                    {
                        cout << endl;
                        cout << "total price of your cart is " << it->getCart().get_total_price(store.getProducts()) << endl;
                    }

                    if(customer_choose == 5)
                        it->getCart().reset();

                    if(customer_choose == 6)
                    {
                        cout << "I do not know how to write check out in cart!" << endl;
                        if(it->getBalance() < it->getCart().get_total_price(store.getProducts()))
                            throw invalid_argument("your balance is not enough!");
                        it->getCart().check_out(store.getStock());
                        it->convert_cart_to_receipt(store.getProducts());
                    }

                    if(customer_choose == 7)
                        cout << endl << "total price of all of receipt is " << it->get_tatal_purchace_amount(store.getProducts()) << endl;

                    customer_page(store);
                }
            }

            if(store_choose == 8)
            {
                int stock_choose;
                stock_page(store);
                while(cin >> stock_choose)
                {
                    if(stock_choose == 1)
                        store.getStock().view_stock();

                    if(stock_choose == 2)
                    {
                        int product_id;
                        cout << endl;
                        cout << "------------------------------------COUNT OF PRODUCT------------------------------------" << endl;
                        cout << "product id: ";
                        cin >> product_id;

                        if(store.find_product(product_id) == -1)
                            throw invalid_argument("Product id is wrong!");

                        cout << endl;
                        cout << store.getStock().get_count(product_id) << " of " << product_id << " is available in stock" << endl;
                    }

                    if(stock_choose == 3)
                    {
                        int product_id;
                        int quantity;
                        cout << endl;
                        cout << "------------------------------------CHANGE COUNT OF PRODUCT IN STOCK------------------------------------" << endl;
                        cout << "product id: ";
                        cin >> product_id;

                        if(store.find_product(product_id) == -1)
                            throw invalid_argument("Product id is wrong!");

                        cout << "quantity of product: ";
                        cin >> quantity;

                        if(store.find_product(product_id) + quantity < 0)
                            throw invalid_argument("count of product can not negative!");

                        store.getStock().change_count_by(product_id, quantity);
                    }

                    if(stock_choose == 4)
                        break;

                    stock_page(store);
                }
            }

            if(store_choose == 9)
                store.save_to_file();

            if(store_choose == 10)
                return 0;
        }


        catch(invalid_argument &err)
        {
            cout << endl;
            cout << err.what() << endl;
        }
        home_page(store);
    }
    return 0;
}

void home_page(Store &store)
{

    cout << endl << "-----------------------------HOME PAGE-----------------------------" << endl;
    cout << "1. Add product\n2. Add customer\n3. View product\n4. View customer\n5. check out\n"
         << "6. sales report\n7. Customer page\n8. Stock page\n9. Save to file\n10. Exit" << endl;
    cout << "Please enter a number: ";
}

void customer_page(Store &store)
{
    cout << endl << "---------------------------CUSTOMER PAGE---------------------------" << endl;
    cout << "1. add to cart\n2. remove item from cart\n3. view cart\n4. total price of cart\n"
         <<  "5. clear cart\n6. check out\n7. total purchase amount\n8. return to home page" << endl;
    cout << "Please enter a number: ";
}

void stock_page(Store &store)
{
    cout << endl << "---------------------------STOCK PAGE---------------------------" << endl;
    cout << "1. view stock\n2. get count of product in stock\n3. change count of product in stock\n4. return to home page" << endl;
    cout << "Please enter a number: ";
}

void load_file(Store &store)
{
    {
        int id;
        string name;
        float price;
        string brand;
        string expire_date;

        Product product;

        ifstream productFile("product.txt");

        if(!productFile)
            throw invalid_argument("product.txt is not open correctly!");

        while(productFile >> id)
        {
            //getline(productFile, name);
            productFile >> name;
            productFile >> price;
            //getline(productFile, brand);
            productFile >> brand;
            //productFile >> expire_date;
            productFile >> expire_date;

            product.setId(id);
            product.setName(name);
            product.setPrice(price);
            product.setBrand(brand);
            product.setExpire_date(expire_date);

            store.getProducts().push_back(product);
        }
        productFile.close();
    }

    {
        int id;
        string name;
        string phone_number;
        string address;
        float balance;

        Customer customer;

        ifstream customerFile("customer.txt");

        if(!customerFile)
            throw invalid_argument("customer.txt is not open correctly!");

        while(customerFile >> id)
        {
            //getline(customerFile, name);
            customerFile >> name;
            //getline(customerFile, phone_number);
            customerFile >> phone_number;
            //getline(customerFile, address);
            customerFile >> address;
            customerFile >> balance;

            customer.setId(id);
            customer.setName(name);
            customer.setPhoneNumber(phone_number);
            customer.setAddress(address);
            customer.setBalance(balance);

            store.getCustomers().push_back(customer);
        }
        customerFile.close();
    }

    {
        int id;
        int quantity;

        ifstream stockFile("stock.txt");

        if(!stockFile)
            throw invalid_argument("stock.txt is not open correctly!");

        while(stockFile >> id)
        {
            stockFile >> quantity;

            store.getStock().getItems().insert(pair<int, int>(id, quantity));
        }
        stockFile.close();
    }

    {
        int customerId;
        int count_of_pair;
        int productId;
        int quantity;

        ifstream cartFile("cart.txt");

        if(!cartFile)
            throw invalid_argument("cart.txt is not open correctly!");

        while(cartFile >> customerId)
        {
            cartFile >> count_of_pair;
            for(auto it = store.getCustomers().begin(); it != store.getCustomers().end(); it++)
            {
                if(it->getId() == customerId)
                {
                    for(int i = 0; i < count_of_pair; i++)
                    {
                        cartFile >> productId;
                        cartFile >> quantity;

                        it->getCart().getItems().insert(pair<int, int>(productId, quantity));
                    }
                    break;
                }
            }
        }
        cartFile.close();
    }


    {
        int customer_id;
        int count_of_receipt;
        int count_of_pair;
        int product_id;
        int quantity_of_product;
        string date;

        ifstream receiptFile("receipt.txt");

        if(!receiptFile)
            throw invalid_argument("receipt.txt is not open correctly!");

        while(receiptFile >> customer_id)
        {
            for(auto it = store.getCustomers().begin(); it != store.getCustomers().end(); it++)
            {
                if(it->getId() == customer_id)
                {
                    receiptFile >> count_of_receipt;
                    for(int i = 0; i < count_of_receipt; i++)
                    {
                        Receipt receipt;
                        receiptFile >> count_of_pair;
                        for(int j = 0; j < count_of_pair; j++)
                        {
                            receiptFile >> product_id;
                            receiptFile >> quantity_of_product;

                            receipt.getItems().insert(pair<int, int>(product_id, quantity_of_product));
                        }
                        receiptFile >> date;
                        receipt.setDate(date);

                        it->getHistory().push_back(receipt);
                    }
                    break;
                }
            }
        }
        receiptFile.close();
    }

}
