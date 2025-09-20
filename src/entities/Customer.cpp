//
// Created by iznets on 9/20/25.
//
#include "../../include/entities/Customer.h"

// constructor
Customer::Customer(const std::string& u, const std::string& p)
    : username(u), phone(p), total_orders(0), total_spent(0.0), discount(0.0) {}

// getters
std::string Customer::getUsername() const { return username; }
std::string Customer::getPhone() const { return phone; }
int Customer::getTotalOrders() const { return total_orders; }
double Customer::getTotalSpent() const { return total_spent; }
double Customer::getDiscount() const { return discount; }

// setters
void Customer::setPhone(const std::string& p) { phone = p; }
void Customer::setDiscount(double d) { discount = d; }

// update methods
void Customer::addOrder(double amount) {
    total_orders++;
    total_spent += amount;
}