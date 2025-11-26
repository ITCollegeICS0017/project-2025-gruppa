#pragma once
#include <string>
#include <vector>
#include "Product.h"
#include <chrono>

#include "types/OrderStatusEnum.h"

enum class OrderStatus;
using namespace std;

class Order
{
private:
    int id;
    vector<Product> products;
    string delivery_address;
    double total_price;
    chrono::system_clock::time_point order_time;
    chrono::system_clock::time_point delivery_date;
    OrderStatus status;

public:
    Order(
        int id,
        vector<Product> products,
        string delivery_address,
        chrono::system_clock::time_point order_time,
        chrono::system_clock::time_point delivery_date,
        OrderStatus status = OrderStatus::Scheduled);

    // Getters
    int getId() const;
    vector<Product> getProducts() const;
    string getDeliveryAddress() const;
    double getTotalPrice() const;
    chrono::system_clock::time_point getOrderTime() const;
    chrono::system_clock::time_point getDeliveryDate() const;
    OrderStatus getStatus() const;

    // Setters
    void setId(int new_id);
    void setProducts(const vector<Product>& new_products);
    void setDeliveryAddress(const string& new_address);
    void setTotalPrice(double new_price);
    void setOrderTime(const chrono::system_clock::time_point& new_order_time);
    void setDeliveryDate(const chrono::system_clock::time_point& new_delivery_date);
    void setStatus(OrderStatus new_status);
};
