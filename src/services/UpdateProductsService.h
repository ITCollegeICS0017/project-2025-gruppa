#ifndef PROJECT_2025_GRUPPA_UPDATEPRODUCTSSERVICE_H
#define PROJECT_2025_GRUPPA_UPDATEPRODUCTSSERVICE_H

#pragma once

#include <string>
#include "../domain/Product.h"

class UpdateProductsService {
private:
    std::string dbFilePath;

    int getNextId() const;

public:
    explicit UpdateProductsService(const std::string &dbFilePath = "src/database/products.csv");

    Product addProduct(
        const std::string &name,
        const std::string &description,
        double price,
        int quantity
    );

    bool deleteProductById(int id);
};

#endif // PROJECT_2025_GRUPPA_UPDATEPRODUCTSSERVICE_H
