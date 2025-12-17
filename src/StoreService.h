#pragma once
#include <string>
#include <vector>
#include "domain/Product.h"

class StoreService {
private:
    std::vector<Product> products;

public:
    StoreService();

    void loadProducts();

    void addProduct();

    void customerMenu(const std::string& username);

    void adminMenu();

    void loginMenu();
};

// Validation and Error Policies
std::string readNonEmptyString(const std::string& prompt);
void validatePrice(double price);
void validateQuantity(int quantity);
bool productExists(const std::vector<Product>& products, int id);
