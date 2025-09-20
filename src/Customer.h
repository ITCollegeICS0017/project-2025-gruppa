//
// Created by shevt on 20.09.2025.
//

#ifndef PROJECT_2025_GRUPPA_CUSTOMER_H
#define PROJECT_2025_GRUPPA_CUSTOMER_H

#include <string>
using namespace std;

class Customer {
private:
    std::string username;
    int balance;

public:
    Customer(std::string u);
    int add_money(int b);
    void get_balance() const;
};


#endif //PROJECT_2025_GRUPPA_CUSTOMER_H