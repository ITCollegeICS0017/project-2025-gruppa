//
// Created by iznets on 9/20/25.
//

#include "../../include/entities/Order.h"

// constructor
Order::Order(const std::string& customer, const std::string& date)
    : customer_username(customer),
      delivery_date(date),
      status(OrderStatus::Pending),
      subtotal(0.0),
      discount_amount(0.0),
      total(0.0) {}

// getters
std::string Order::getCustomerUsername() const { return customer_username; }
std::vector<OrderItem> Order::getItems() const { return items; }
std::string Order::getDeliveryDate() const { return delivery_date; }
OrderStatus Order::getStatus() const { return status; }  // << enum
double Order::getSubtotal() const { return subtotal; }
double Order::getDiscountAmount() const { return discount_amount; }
double Order::getTotal() const { return total; }

// setters
void Order::setDeliveryDate(const std::string& date) { delivery_date = date; }
void Order::setStatus(OrderStatus s) { status = s; }   // << enum
void Order::setDiscountAmount(double d) { discount_amount = d; }

// update methods
void Order::addItem(int prod_id, int qty, double unit_price) {
    items.emplace_back(prod_id, qty, unit_price);
    calculateTotals();
}

void Order::calculateTotals() {
    subtotal = 0.0;
    for (const auto& item : items) {
        subtotal += item.qty * item.unit_price;
    }
    total = subtotal - discount_amount;
    if (total < 0) total = 0.0;
}