#ifndef PROJECT_2025_GRUPPA_CUSTOMERSERVICE_H
#define PROJECT_2025_GRUPPA_CUSTOMERSERVICE_H

#pragma once
#include <vector>
#include <string>
#include "../domain/Product.h"
#include "../domain/Customer.h"

class CustomerService
{
private:
    std::vector<Product> products;

public:
    CustomerService();

    void loadProducts();
    void customerMenu();
};

#endif // PROJECT_2025_GRUPPA_CUSTOMERSERVICE_H
