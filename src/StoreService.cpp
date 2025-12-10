#include "StoreService.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <stdexcept>
#include <optional>

#include "domain/Administrator.h"
#include "domain/Customer.h"
#include "services/SearchService.h"

using namespace std;

// UI VALIDATION
string readNonEmptyString(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);

        if (!input.empty() && input.find_first_not_of(" \t\n\r") != string::npos) {
            return input;
        }

        cout << "Input cannot be empty. Try again.\n";
    }
}

// LOGIC VALIDATION
void validatePrice(double price) {
    if (price <= 0) {
        throw runtime_error("Price must be greater than 0.");
    }
}

// ERROR POLICY
void validateQuantity(int quantity) {
    if (quantity <= 0) {
        throw runtime_error("Quantity must be greater than 0.");
    }
}

// REPOSITORY VALIDATION
bool productExists(const vector<Product>& products, int id) {
    for (const auto& p : products) {
        if (p.getId() == id) return true;
    }
    return false;
}


StoreService::StoreService() {
    loadProducts();
}

void StoreService::loadProducts() {
    products.clear();

    SearchService searchService("../database/products.csv");
    products = searchService.findByPriceRange(std::nullopt, std::nullopt);
}

void StoreService::addProduct() {
    while (true) {
        string name, description;
        double price;
        int quantity;

        cout << "\n-- Add New Product --\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        name = readNonEmptyString("Product name: ");
        description = readNonEmptyString("Product description: ");

        cout << "Product price: ";
        cin >> price;
        cout << "Product quantity: ";
        cin >> quantity;

        try {
            validatePrice(price);
            validateQuantity(quantity);
        } catch (const exception& ex) {
            cout << "Error: " << ex.what() << "\nTry again.\n";
            continue;
        }

        cout << "\nReview:\n";
        cout << "Name: " << name << "\nDescription: " << description
             << "\nPrice: " << price << "\nQuantity: " << quantity << "\n\n";

        cout << "Confirm action:\n1 - Save\n2 - Cancel\n3 - Edit\nChoice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            const int id = products.size() + 1;
            products.emplace_back(id, name, description, price, quantity);
            cout << "Product added successfully!\n";
            return;
        }
        if (choice == 2) {
            cout << "Operation cancelled.\n";
            adminMenu();
            break;
        }
        if (choice == 3) {
            cout << "Restarting product entry...\n";
        } else {
            cout << "Unknown option. Try again.\n";
        }
    }
}

void StoreService::customerMenu() {
    cout << "\n--- Customer Menu ---\nFeature not implemented yet.\n";
}

void StoreService::adminMenu() {
    int choice;
    while (true) {
        cout << "\n--- Admin Menu ---"
                "\n1. Add product"
                "\n2. View products"
                "\n3. Delete product"
                "\n0. Logout"
                "\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1: addProduct(); break;
            case 2:
                cout << "\n--- Product List ---\n";
                for (const auto &p: products) {
                    cout << p.getId() << ". " << p.getName()
                         << " - $" << p.getPrice()
                         << " (" << p.getQuantity() << " left)\n";
                }
                break;
            case 3: {
                cout << "Enter product ID to delete: ";
                int id;
                cin >> id;

                if (!productExists(products, id)) {
                    cout << "Error: Product ID does not exist.\n";
                    break;
                }

                products.erase(
                    remove_if(products.begin(), products.end(),
                              [id](const Product& p){ return p.getId() == id; }),
                    products.end()
                );

                cout << "Product deleted successfully.\n";
                break;
            }
            case 0:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Unknown option.\n";
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
