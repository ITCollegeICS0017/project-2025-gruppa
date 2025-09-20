//
// Created by shevt on 20.09.2025.
//
#include <iostream>  // for std::cin and std::cout
#include <string>    // for std::string
#include "Customer.h"
#include "Customer.cpp"

int main() {
    std::string userInput;

    std::cout << "Enter username: ";
    std::cin >> userInput;

    Customer customer(userInput);

    int balance;
    std::cout << "Enter balance: ";
    std::cin >> balance;

    customer.add_money(balance);
    customer.get_balance();

    return 0;
}