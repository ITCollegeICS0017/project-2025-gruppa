#include "StoreService.h"
#include "services/OrderService.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <stdexcept>
#include <optional>

#include "domain/Administrator.h"
#include "domain/Customer.h"
#include "services/LoadProductsService.h"

using namespace std;

// PRODUCT SEARCH
void searchUI(const std::vector<Product>& inventory);

// UI VALIDATION
string readNonEmptyString(const string& prompt)
{
    string input;
    while (true)
    {
        cout << prompt;
        getline(cin, input);

        if (!input.empty() && input.find_first_not_of(" \t\n\r") != string::npos)
        {
            return input;
        }

        cout << "Input cannot be empty. Try again.\n";
    }
}

// LOGIC VALIDATION
void validatePrice(double price)
{
    if (price <= 0)
    {
        throw runtime_error("Price must be greater than 0.");
    }
}

// ERROR POLICY
void validateQuantity(int quantity)
{
    if (quantity <= 0)
    {
        throw runtime_error("Quantity must be greater than 0.");
    }
}

// REPOSITORY VALIDATION
bool productExists(const vector<Product>& products, int id)
{
    for (const auto& p : products)
    {
        if (p.getId() == id) return true;
    }
    return false;
}


StoreService::StoreService()
{
    loadProducts();
}

void StoreService::loadProducts()
{
    products.clear();

    LoadProductsService searchService("database/products.csv");
    products = searchService.findByPriceRange(std::nullopt, std::nullopt);
}

void StoreService::addProduct()
{
    while (true)
    {
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

        try
        {
            validatePrice(price);
            validateQuantity(quantity);
        }
        catch (const exception& ex)
        {
            cout << "Error: " << ex.what() << "\nTry again.\n";
            continue;
        }

        cout << "\nReview:\n";
        cout << "Name: " << name << "\nDescription: " << description
            << "\nPrice: " << price << "\nQuantity: " << quantity << "\n\n";

        cout << "Confirm action:\n1 - Save\n2 - Cancel\n3 - Edit\nChoice: ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            const int id = products.size() + 1;
            products.emplace_back(id, name, description, price, quantity);
            cout << "Product added successfully!\n";
            return;
        }
        if (choice == 2)
        {
            cout << "Operation cancelled.\n";
            adminMenu();
            break;
        }
        if (choice == 3)
        {
            cout << "Restarting product entry...\n";
        }
        else
        {
            cout << "Unknown option. Try again.\n";
        }
    }
}

void StoreService::customerMenu()
{
    int choice;
    std::string username;

    cout << "\nEnter your username: ";
    cin >> username;

    while (true)
    {
        cout << "\n--- Customer Menu ---"
            "\n1. Search products"
            "\n2. View products"
            "\n3. View orders"
            "\n0. Logout"
            "\nChoice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                searchUI(products);
                break;

            case 2:
                cout << "\n--- Product List ---\n";
                for (const auto& p : products)
                {
                    cout << p.getId() << ". " << p.getName()
                        << " - $" << p.getPrice()
                        << " (" << p.getQuantity() << " left)\n";
                }
                break;

            case 3:
            {
                cout << "\n--- Your Orders ---\n";
                OrderService service("database/orders.csv");
                auto orders = service.getOrdersByUser(username);

                if (orders.empty()) {
                    cout << "You have no orders.\n";
                    break;
                }

                for (const auto& o : orders)
                {
                    cout << "Order #" << o.getId()
                         << " | Product ID: " << o.getProductId()
                         << " | Date: " << o.getDate()
                         << " | Status: " << statusToString(o.getStatus())
                         << "\n";
                }
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



// === SEARCH ===
std::string toLowerCase(std::string str)
{
    // Transform the string in-place to lowercase
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return str;
}

double getValidDouble(const std::string& prompt)
{
    std::string input;
    while (true)
    {
        std::cout << prompt;
        std::getline(std::cin, input);

        if (input.empty()) return -1.0; // Handle empty input

        try
        {
            size_t pos;
            double val = std::stod(input, &pos);
            if (pos == input.length()) return val; // Successfully parsed entire string
        }
        catch (...)
        {
        }

        std::cout << "Invalid price. Please enter a number or press Enter to skip.\n";
    }
}

std::vector<const Product*> searchProducts(const std::vector<Product>& inventory,
                                           std::string nameQuery, // Passed by value to modify
                                           std::string descQuery, // Passed by value to modify
                                           double minPrice,
                                           double maxPrice)
{
    std::vector<const Product*> matches;

    // 1. Pre-process queries (convert to lowercase once)
    nameQuery = toLowerCase(nameQuery);
    descQuery = toLowerCase(descQuery);

    for (const auto& p : inventory)
    {
        // 2. Check Name (Compare lowercase vs lowercase)
        if (!nameQuery.empty())
        {
            std::string pName = toLowerCase(p.getName());
            if (pName.find(nameQuery) == std::string::npos) continue;
        }

        // 3. Check Description (Compare lowercase vs lowercase)
        if (!descQuery.empty())
        {
            std::string pDesc = toLowerCase(p.getDescription());
            if (pDesc.find(descQuery) == std::string::npos) continue;
        }

        // 4. Check Price Bounds (Unchanged)
        if (minPrice != -1.0 && p.getPrice() < minPrice) continue;
        if (maxPrice != -1.0 && p.getPrice() > maxPrice) continue;

        matches.push_back(&p);
    }
    return matches;
}

void searchUI(const std::vector<Product>& inventory)
{
    std::cout << "\n--- Search Products ---\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // ... Input gathering code remains the same ...
    std::string name, desc;
    std::cout << "Name (contains): ";
    std::getline(std::cin, name);
    double minP = getValidDouble("Min Price: ");
    double maxP = getValidDouble("Max Price: ");
    std::cout << "Description (contains): ";
    std::getline(std::cin, desc);

    // Call Logic
    std::vector<const Product*> results = searchProducts(inventory, name, desc, minP, maxP);

    // Display Results directly
    std::cout << "\nFound " << results.size() << " product(s):\n";
    for (const Product* p : results)
    {
        // Access members directly via arrow operator (->)
        std::cout << "ID: " << p->getId()
            << " | " << p->getName()
            << " | $" << p->getPrice() << "\n";
    }
}


void StoreService::adminMenu()
{
    int choice;
    while (true)
    {
        cout << "\n--- Admin Menu ---"
                "\n1. Add product menu"
                "\n2. View products"
                "\n3. Delete product"
                "\n4. View all orders"
                "\n0. Logout"
                "\nChoice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: addProduct();
            break;
        case 2:
            cout << "\n--- Product List ---\n";
            for (const auto& p : products)
            {
                cout << p.getId() << ". " << p.getName()
                    << " - $" << p.getPrice()
                    << " (" << p.getQuantity() << " left)\n";
            }
            break;
        case 3:
            {
                cout << "Enter product ID to delete: ";
                int id;
                cin >> id;

                if (!productExists(products, id))
                {
                    cout << "Error: Product ID does not exist.\n";
                    break;
                }

                products.erase(
                    remove_if(products.begin(), products.end(),
                              [id](const Product& p) { return p.getId() == id; }),
                    products.end()
                );

                cout << "Product deleted successfully.\n";
                break;
            }
        case 4:
        {
            cout << "\n--- ALL ORDERS ---\n";
            OrderService service("database/orders.csv");
            auto orders = service.getOrdersByUser("admin"); // admin sees all

            if (orders.empty()) {
                cout << "No orders in the system.\n";
                break;
            }

            for (const auto& o : orders)
            {
                cout << "Order #" << o.getId()
                     << " | Product ID: " << o.getProductId()
                     << " | Date: " << o.getDate()
                     << " | Status: " << statusToString(o.getStatus())
                     << "\n";
            }
            break;
        }
        case 0:
            cout << "Logging out...\n";
            return;
        case 9: searchUI(products);
            break;
        default:
            cout << "Unknown option.\n";
        }
    }
}

void StoreService::loginMenu()
{
    string username;
    cout << "Enter your username: ";
    cin >> username;

    if (username == "admin")
    {
        Administrator admin("admin");
        adminMenu();
    }
    else
    {
        Customer customer(username);
        customerMenu();
    }
}
