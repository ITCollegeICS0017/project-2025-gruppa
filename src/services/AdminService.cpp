#include "AdminService.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace {
    int readAdminMenuChoice() {
        while (true) {
            std::string input;
            std::cout << "Choice: ";
            std::cin >> input;

            try {
                if (input.size() != 1 || input[0] < '0' || input[0] > '2') {
                    throw std::invalid_argument("Invalid menu choice.");
                }

                return input[0] - '0';
            } catch (const std::invalid_argument &ex) {
                std::cout << "Input error: " << ex.what() << '\n';
            }
        }
    }
}

AdminService::AdminService() {
    loadProducts();
}

void AdminService::loadProducts() {
    products.clear();

    struct Seed {
        int id;
        const char *name;
        const char *description;
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

    for (const auto &s: seeds) {
        products.emplace_back(s.id, s.name, s.description, s.price, s.quantity);
    }
}

void AdminService::addProduct() {
    while (true) {
        std::string name;
        std::string description;
        double price;
        int quantity;

        std::cout << "\n-- Add New Product --\n";

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Product name: ";
        std::getline(std::cin, name);

        std::cout << "Product description: ";
        std::getline(std::cin, description);

        std::cout << "Product price: ";
        std::cin >> price;

        std::cout << "Product quantity: ";
        std::cin >> quantity;

        std::cout << "\nReview:\n";
        std::cout << "Name: " << name << "\n";
        std::cout << "Description: " << description << "\n";
        std::cout << "Price: " << price << "\n";
        std::cout << "Quantity: " << quantity << "\n\n";

        std::cout << "Confirm action:\n";
        std::cout << "1 - Save\n";
        std::cout << "2 - Cancel (exit)\n";
        std::cout << "3 - Edit (re-enter data)\n";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            const int id = static_cast<int>(products.size()) + 1;
            const Product newProduct(id, name, description, price, quantity);
            products.push_back(newProduct);

            std::cout << "\nProduct added successfully!\n";
            std::cout << "ID: " << newProduct.getId() << "\n";
            std::cout << "Name: " << newProduct.getName() << "\n";
            std::cout << "Description: " << newProduct.getDescription() << "\n";
            std::cout << "Price: " << newProduct.getPrice() << "\n";
            std::cout << "Quantity: " << newProduct.getQuantity() << "\n";
            return;
        }
        if (choice == 2) {
            std::cout << "Operation cancelled.\n";
            adminMenu();
            break;
        }
        if (choice == 3) {
            std::cout << "\nRestarting product entry...\n";
        } else {
            std::cout << "Unknown option. Try again. \n";
        }
    }
}

void AdminService::adminMenu() {
    while (true) {
        std::cout << "\n--- Admin Menu ---\n"
                << "1. Add product\n"
                << "2. View products\n"
                << "0. Logout\n";

        int choice = readAdminMenuChoice();

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                std::cout << "\n--- Product List ---\n";
                for (const auto &p: products) {
                    std::cout << p.getId() << ". " << p.getName()
                            << " - $" << p.getPrice()
                            << " (" << p.getQuantity() << " left)\n";
                }
                break;
            case 0:
                std::cout << "Logging out...\n";
                return;
            default:
                // theoretically unreachable
                std::cout << "Unknown option.\n";
                break;
        }
    }
}
