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
