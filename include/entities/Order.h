//
// Created by iznets on 9/20/25.
//

#ifndef PROJECT_2025_GRUPPA_ORDER_H
#define PROJECT_2025_GRUPPA_ORDER_H

#include <string>
#include <vector>
#include "../common/OrderStatus.h"

// item inside order
struct OrderItem {
    int prod_id;
    int qty;
    double unit_price;

    OrderItem(int id, int q, double price)
        : prod_id(id), qty(q), unit_price(price) {}
};

// main order class
class Order {
private:
    int id;
    std::string customer_username;
    std::vector<OrderItem> items;
    std::string delivery_date;   // "YYYY-MM-DD"
    OrderStatus status;
    double subtotal;
    double discount_amount;
    double total;

public:
    // constructor
    Order(const std::string& customer, const std::string& date);

    // getters
    int getId() const;
    std::string getCustomerUsername() const;
    std::vector<OrderItem> getItems() const;
    std::string getDeliveryDate() const;
    OrderStatus getStatus() const;
    double getSubtotal() const;
    double getDiscountAmount() const;
    double getTotal() const;

    // setters
    void setDeliveryDate(const std::string& date);
    void setStatus(OrderStatus s);
    void setDiscountAmount(double d);

    // update methods
    void addItem(int prod_id, int qty, double unit_price);
    void calculateTotals();

    static void notify(const std::string& id, int product_id);
};

#endif //PROJECT_2025_GRUPPA_ORDER_H