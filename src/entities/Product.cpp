//
// Created by iznets on 9/20/25.
//
#include "../../include/entities/Product.h"

// constructor
Product::Product(const std::string& n, const std::string& d, double p, int q)
    : name(n), description(d), price(p), quantity(q) {}

// getters
std::string Product::getName() const { return name; }
std::string Product::getDescription() const { return description; }
double Product::getPrice() const { return price; }
int Product::getQuantity() const { return quantity; }

// setters
void Product::setName(const std::string& n) { name = n; }
void Product::setDescription(const std::string& d) { description = d; }
void Product::setPrice(double p) { price = p; }
void Product::setQuantity(int q) { quantity = q; }

// update methods
void Product::reduceQuantity(int q) {
    if (q <= quantity) {
        quantity -= q;
    }
}

void Product::addQuantity(int q) {
    if (q > 0) {
        quantity += q;
    }
}