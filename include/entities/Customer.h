//
// Created by iznets on 9/20/25.
//

#ifndef PROJECT_2025_GRUPPA_CUSTOMER_H
#define PROJECT_2025_GRUPPA_CUSTOMER_H

#include <string>

#include "Administrator.h"

// simple entity class
class Customer {
private:
    std::string username;
    std::string phone;
    int total_orders;
    double total_spent;
    double discount;

public:
    // constructor
    Customer(const std::string& u, const std::string& p);

    // getters
    std::string getUsername() const;
    std::string getPhone() const;
    int getTotalOrders() const;
    double getTotalSpent() const;
    double getDiscount() const;

    // setters
    void setPhone(const std::string& p);
    void setDiscount(double d);

    // update methods
    void addOrder(double amount); // +1 order, +amount to total_spent

    static void viewProduct(const Product& p); // Placeholder
};

#endif //PROJECT_2025_GRUPPA_CUSTOMER_H