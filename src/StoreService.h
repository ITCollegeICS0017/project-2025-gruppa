#ifndef PROJECT_2025_GRUPPA_STORESERVICE_H
#define PROJECT_2025_GRUPPA_STORESERVICE_H


#pragma once
#include <vector>
#include <string>
#include "Product.h"
#include "Administrator.h"
#include "Customer.h"
using namespace std;

class StoreService {
private:
    vector<Product> products;

public:
    StoreService();

    void loadProducts();
    void addProduct();
    void loginMenu();
    void customerMenu();
    void adminMenu();
};



#endif //PROJECT_2025_GRUPPA_STORESERVICE_H