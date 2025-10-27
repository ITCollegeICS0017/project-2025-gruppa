#include "StoreService.h"
#include <iostream>
#include <limits>
using namespace std;

StoreService::StoreService() {
    loadProducts();
}

void StoreService::loadProducts() {
    products.clear();

    struct Seed {
        int id;
        const char* name;
        const char* description;
        double price;
        int quantity;
    };

    static const Seed seeds[] = {
        {1,  "iPhone 17 Pro",      "Latest Apple phone",        1200.99, 5},
        {2,  "Galaxy S25",         "Flagship Samsung phone",    1100.49, 3},
        {3,  "Pixel 9",            "Google’s new phone",         999.99, 4},
        {4,  "MacBook Air M4",     "Lightweight Apple laptop",  1599.99, 2},
        {5,  "Dell XPS 15",        "High-performance laptop",   1399.50, 6},
        {6,  "Sony WH-1000XM6",    "Noise-cancelling headphones",399.00,10},
        {7,  "iPad Pro",           "12.9-inch Apple tablet",    1199.99, 4},
        {8,  "Apple Watch Ultra 2","Premium smartwatch",         899.49, 7},
        {9,  "Kindle Oasis",       "E-reader with lighting",     249.99, 8},
        {10, "GoPro Hero 13",      "Action camera",              499.95, 5}
    };

    for (const auto& s : seeds) {
        products.emplace_back(s.id, s.name, s.description, s.price, s.quantity);
    }
}

void StoreService::addProduct() {
    while (true) {
        string name;
        string description;
        double price;
        int quantity;

        cout << "\n-- Add New Product --\n";

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Product name: ";
        getline(cin, name);

        cout << "Product description: ";
        getline(cin, description);

        cout << "Product price: ";
        cin >> price;

        cout << "Product quantity: ";
        cin >> quantity;

        cout << "\nReview:\n";
        cout << "Name: " << name << "\n";
        cout << "Description: " << description << "\n";
        cout << "Price: " << price << "\n";
        cout << "Quantity: " << quantity << "\n\n";

        cout << "Confirm action:\n";
        cout << "1 - Save\n";
        cout << "2 - Cancel (exit)\n";
        cout << "3 - Edit (re-enter data)\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            const int id = products.size() + 1;
            const Product new_product(id, name, description, price, quantity);
            products.push_back(new_product);

            cout << "\nProduct added successfully!\n";
            cout << "ID: " << new_product.getId() << "\n";
            cout << "Name: " << new_product.getName() << "\n";
            cout << "Description: " << new_product.getDescription() << "\n";
            cout << "Price: " << new_product.getPrice() << "\n";
            cout << "Quantity: " << new_product.getQuantity() << "\n";
            return;
        } if (choice == 2) {
            cout << "Operation cancelled.\n";
            adminMenu();
            break;
        } if (choice == 3) {
            cout << "\nRestarting product entry...\n";
        } else {
            cout << "Unknown option. Try again. \n";
        }
    }
}

void StoreService::customerMenu() {
    cout << "\n--- Customer Menu ---\n";
    cout << "Feature not implemented yet.\n";
}

void StoreService::adminMenu() {
    int choice;
    while (true) {
        cout << "\n--- Admin Menu ---\n"
                << "1. Add product\n"
                << "2. View products\n"
                << "0. Logout\n"
                << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                cout << "\n--- Product List ---\n";
                for (const auto &p: products) {
                    cout << p.getId() << ". " << p.getName()
                            << " - $" << p.getPrice()
                            << " (" << p.getQuantity() << " left)\n";
                }
                break;
            case 0:
                cout << "Logging out...\n";
                return; // exits adminMenu and returns to loginMenu caller
            default:
                cout << "Unknown option.\n";
                break;
        }
    }
}

void StoreService::loginMenu() {
    string username;
    cout << "Enter your username: ";
    cin >> username;

    if (username == "admin") {
        Administrator admin("admin");
        adminMenu();
    } else {
        Customer customer(username);
        customerMenu();
    }
}


