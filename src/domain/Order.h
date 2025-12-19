#pragma once
#include <string>
#include "types/OrderStatusEnum.h"

class Order {
private:
    int id;
    std::string user;
    int productId;
    std::string date;
    OrderStatus status;

public:
    Order(int id, const std::string& user, int productId,
          const std::string& date, OrderStatus status)
        : id(id), user(user), productId(productId), date(date), status(status) {}

    int getId() const { return id; }
    const std::string& getUser() const { return user; }
    int getProductId() const { return productId; }
    const std::string& getDate() const { return date; }
    OrderStatus getStatus() const { return status; }
};
