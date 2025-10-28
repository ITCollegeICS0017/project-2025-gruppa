#include "CustomerService.h"
#include <iostream>
#include <limits>

CustomerService::CustomerService()
{
    loadProducts();
}

void CustomerService::loadProducts()
{
    products.clear();

    struct Seed
    {
        int id;
        const char* name;
        const char* description;
        double price;
        int quantity;
    };

    static const Seed seeds[] = {
        {1, "iPhone 17 Pro", "Latest Apple phone", 1200.99, 5},
        {2, "Galaxy S25", "Flagship Samsung phone", 1100.49, 3},
        {3, "Pixel 9", "Google’s new phone", 999.99, 4},
        {4, "MacBook Air M4", "Lightweight Apple laptop", 1599.99, 2},
        {5, "Dell XPS 15", "High-performance laptop", 1399.50, 6},
        {6, "Sony WH-1000XM6", "Noise-cancelling headphones", 399.00, 10},
        {7, "iPad Pro", "12.9-inch Apple tablet", 1199.99, 4},
        {8, "Apple Watch Ultra 2", "Premium smartwatch", 899.49, 7},
        {9, "Kindle Oasis", "E-reader with lighting", 249.99, 8},
        {10, "GoPro Hero 13", "Action camera", 499.95, 5}
    };

    for (const auto& s : seeds)
    {
        products.emplace_back(s.id, s.name, s.description, s.price, s.quantity);
    }
}

void CustomerService::customerMenu()
{
    int choice;
    while (true)
    {
        std::cout << "\n--- Customer Menu ---\n"
            << "1. View Orders\n"
            << "2. View products\n"
            << "0. Logout\n"
            << "Choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 0:
            std::cout << "Logging out...\n";
            return;
        case 1:
            // Not implemented
            break;
        case 2:
            // Not implemented
            break;
        default:
            std::cout << "Unknown option.\n";
            break;
        }
    }
}
