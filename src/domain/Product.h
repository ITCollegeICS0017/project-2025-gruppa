//
// Created by Marat Biryukov on 26.10.2025.
//

#ifndef PROJECT_2025_GRUPPA_PRODUCT_H
#define PROJECT_2025_GRUPPA_PRODUCT_H


#pragma once
#include <string>
using namespace std;

class Product
{
private:
    int id;
    string name;
    string description;
    double price;
    int quantity;

public:
    Product(int id, const string& name, const string& description, double price, int quantity);

    // Getters
    int getId() const;
    string getName() const;
    string getDescription() const;
    double getPrice() const;
    int getQuantity() const;

    // Setters
    void setName(const string& new_name);
    void setDescription(const string& new_description);
    void setPrice(double new_price);
    void setQuantity(int new_quantity);
};


#endif //PROJECT_2025_GRUPPA_PRODUCT_H
