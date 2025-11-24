#include "Product.h"

Product::Product(const int id, const string& name, const string& description, const double price, const int quantity)
    : id(id), name(name), description(description), price(price), quantity(quantity) {}

int Product::getId() const { return id; }
string Product::getName() const { return name; }
string Product::getDescription() const { return description; }
double Product::getPrice() const { return price; }
int Product::getQuantity() const { return quantity; }

void Product::setName(const string& new_name) { name = new_name; }
void Product::setDescription(const string& new_description) { description = new_description; }
void Product::setPrice(const double new_price) { price = new_price; }
void Product::setQuantity(const int new_quantity) { quantity = new_quantity; }
