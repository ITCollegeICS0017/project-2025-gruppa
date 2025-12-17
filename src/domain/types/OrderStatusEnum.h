#pragma once

enum class OrderStatus
{
    Scheduled = 1,
    Delivered = 2,
    Canceled = 3
};

inline OrderStatus orderStatusFromInt(int value)
{
    switch (value)
    {
    case 1: return OrderStatus::Scheduled;
    case 2: return OrderStatus::Delivered;
    case 3: return OrderStatus::Canceled;
    default: return OrderStatus::Scheduled;
    }
}
