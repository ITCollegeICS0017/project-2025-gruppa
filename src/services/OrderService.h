#pragma once
#include <vector>
#include <string>
#include "../domain/Order.h"

class OrderService {
private:
    std::string filepath;

public:
    OrderService(const std::string& filepath);
    std::vector<Order> getOrdersByUser(const std::string& username);
};

inline std::string statusToString(OrderStatus st)
{
    switch (st)
    {
        case OrderStatus::Scheduled: return "Scheduled";
        case OrderStatus::Delivered: return "Delivered";
        case OrderStatus::Canceled:  return "Canceled";
        default:                     return "Unknown";
    }
}
