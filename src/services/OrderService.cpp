#include "OrderService.h"
#include <fstream>
#include <sstream>
#include <iostream>

OrderService::OrderService(const std::string& filepath)
    : filepath(filepath) {}

std::vector<Order> OrderService::getOrdersByUser(const std::string& username)
{
    std::vector<Order> orders;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "❌ ERROR: Cannot open " << filepath << "\n";
        return orders;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string idStr, user, productStr, date, statusStr;

        if (!std::getline(ss, idStr, ';')) continue;
        if (!std::getline(ss, user, ';')) continue;
        if (!std::getline(ss, productStr, ';')) continue;
        if (!std::getline(ss, date, ';')) continue;
        if (!std::getline(ss, statusStr, ';')) continue;

        int id = 0, productId = 0, statusInt = 0;

        try {
            id = std::stoi(idStr);
            productId = std::stoi(productStr);
            statusInt = std::stoi(statusStr);
        } catch (...) {
            std::cerr << "Skipping malformed line: " << line << "\n";
            continue;
        }

        OrderStatus status;
        switch (statusInt)
        {
            case 1: status = OrderStatus::Scheduled; break;
            case 2: status = OrderStatus::Delivered; break;
            case 3: status = OrderStatus::Canceled; break;
            default: status = OrderStatus::Scheduled;
        }

        // ADMIN: see ALL
        if (username == "admin" || username == user)
            orders.emplace_back(id, user, productId, date, status);
    }

    return orders;
}
