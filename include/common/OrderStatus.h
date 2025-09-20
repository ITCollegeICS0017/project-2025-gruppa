//
// Created by iznets on 9/20/25.
//

#ifndef PROJECT_2025_GRUPPA_ORDERSTATUS_H
#define PROJECT_2025_GRUPPA_ORDERSTATUS_H

#include <string>

enum class OrderStatus {
    Pending,
    Scheduled,
    Delivered,
    Cancelled
};


inline const char* to_cstr(OrderStatus s) {
    switch (s) {
    case OrderStatus::Pending:   return "Pending";
    case OrderStatus::Scheduled: return "Scheduled";
    case OrderStatus::Delivered: return "Delivered";
    case OrderStatus::Cancelled: return "Cancelled";
    default:                     return "Unknown";
    }
}


#endif //PROJECT_2025_GRUPPA_ORDERSTATUS_H