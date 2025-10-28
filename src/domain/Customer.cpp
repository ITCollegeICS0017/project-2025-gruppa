#include "Customer.h"

Customer::Customer(const string& username)
    : username(username) {}

string Customer::getUsername() const {
    return username;
}
