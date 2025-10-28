//
// Created by iznets on 10/28/25.
//

#include "Order.h"

Order::Order(
    int id,
    vector<Product> products,
    string delivery_address,
    chrono::system_clock::time_point order_time,
    chrono::system_clock::time_point delivery_date,
    OrderStatus status)
    : id(id),
      products(products),
      delivery_address(delivery_address),
      order_time(order_time),
      delivery_date(delivery_date),
      status(status)
{
    // Calculate total price automatically
    total_price = 0;
    for (const auto& p : products)
    {
        total_price += p.getPrice();
    }
}

// ======= Getters =======

int Order::getId() const { return id; }
vector<Product> Order::getProducts() const { return products; }
string Order::getDeliveryAddress() const { return delivery_address; }
double Order::getTotalPrice() const { return total_price; }
chrono::system_clock::time_point Order::getOrderTime() const { return order_time; }
chrono::system_clock::time_point Order::getDeliveryDate() const { return delivery_date; }
OrderStatus Order::getStatus() const { return status; }

// ======= Setters =======

void Order::setId(int new_id) { id = new_id; }

void Order::setProducts(const vector<Product>& new_products)
{
    products = new_products;
    // Recalculate total price when products change
    total_price = 0;
    for (const auto& p : products)
    {
        total_price += p.getPrice();
    }
}

void Order::setDeliveryAddress(const string& new_address) { delivery_address = new_address; }
void Order::setTotalPrice(double new_price) { total_price = new_price; }
void Order::setOrderTime(const chrono::system_clock::time_point& new_order_time) { order_time = new_order_time; }

void Order::setDeliveryDate(const chrono::system_clock::time_point& new_delivery_date)
{
    delivery_date = new_delivery_date;
}

void Order::setStatus(OrderStatus new_status) { status = new_status; }
