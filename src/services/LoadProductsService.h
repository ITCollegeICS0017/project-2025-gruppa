#ifndef PROJECT_2025_GRUPPA_SEARCHSERVICE_H
#define PROJECT_2025_GRUPPA_SEARCHSERVICE_H

#pragma once

#include <string>
#include <vector>
#include <optional>
#include "../domain/Product.h"

class LoadProductsService {
private:
    std::string dbFilePath;

    std::vector<Product> loadAll() const;

public:
    explicit LoadProductsService(const std::string &dbFilePath = "src/database/products.csv");

    std::optional<Product> findById(int id) const;

    std::vector<Product> findByKeyword(const std::string &keyword) const;

    std::vector<Product> findByPriceRange(
        std::optional<double> minPrice,
        std::optional<double> maxPrice
    ) const;
};

#endif // PROJECT_2025_GRUPPA_SEARCHSERVICE_H
