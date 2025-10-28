//
// Created by Marat Biryukov on 26.10.2025.
//

#ifndef PROJECT_2025_GRUPPA_CUSTOMER_H
#define PROJECT_2025_GRUPPA_CUSTOMER_H


#pragma once
#include <string>
using namespace std;

class Customer {
private:
    string username;

public:
    Customer(const string& username);

    string getUsername() const;
};



#endif //PROJECT_2025_GRUPPA_CUSTOMER_H