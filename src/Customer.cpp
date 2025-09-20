//
// Created by shevt on 20.09.2025.
//

#include "Customer.h"
#include <iostream>
#include <string>
using namespace std;

Customer::Customer(string u) : username(u), balance(0) {}

int Customer::add_money(int money) {
    balance += money;
    return balance;
}

void Customer::get_balance() const {
    std::cout << username << " has " << balance << " euro.\n";
}