#ifndef PROJECT_2025_GRUPPA_ADMINSERVICE_H
#define PROJECT_2025_GRUPPA_ADMINSERVICE_H

#pragma once
#include <vector>
#include <string>
#include "../domain/Product.h"
#include "../domain/Administrator.h"

class AdminService
{
private:
    std::vector<Product> products;

public:
    AdminService();

    void loadProducts();
    void addProduct();
    void adminMenu();
};

#endif // PROJECT_2025_GRUPPA_ADMINSERVICE_H
