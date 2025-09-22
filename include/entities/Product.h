//
// Created by iznets on 9/20/25.
//


#ifndef PROJECT_2025_GRUPPA_PRODUCT_H
#define PROJECT_2025_GRUPPA_PRODUCT_H

#include <string>

// simple entity class
class Product {
private:
    std::string name;
    std::string description;
    double price;
    int quantity;

public:
    // constructor
    Product(const std::string& n, const std::string& d, double p, int q);

    // getters
    std::string getName() const;
    std::string getDescription() const;
    double getPrice() const;
    int getQuantity() const;

    // setters
    void setName(const std::string& n);
    void setDescription(const std::string& d);
    void setPrice(double p);
    void setQuantity(int q);

    // update methods
    void reduceQuantity(int q);  // decrease stock
    void addQuantity(int q);     // increase stock
};

#endif //PROJECT_2025_GRUPPA_PRODUCT_H