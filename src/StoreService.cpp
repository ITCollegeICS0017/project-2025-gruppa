#include "StoreService.h"
#include "services/OrderService.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <stdexcept>
#include <optional>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <map>
#include <cctype>
#include <iomanip>
#include "domain/Administrator.h"
#include "domain/Customer.h"
#include "services/LoadProductsService.h"

using namespace std;

// Helper for writing into file
int getMaxProductId(const std::vector<Product>& products)
{
    int maxId = 0;
    for (const auto& p : products)
    {
        if (p.getId() > maxId) maxId = p.getId();
    }
    return maxId;
}

// Helper for deleting from the file
bool deleteProductFromFile(int id)
{
    const std::string inputPath = "../database/products.csv";
    const std::string tempPath = "../database/products.tmp";

    std::ifstream in(inputPath);
    if (!in.is_open()) return false;

    std::ofstream out(tempPath, std::ios::trunc);
    if (!out.is_open()) return false;

    std::string line;
    bool deleted = false;

    while (std::getline(in, line))
    {
        if (line.empty()) continue;

        if (!std::isdigit(static_cast<unsigned char>(line[0])))
        {
            out << line << '\n';
            continue;
        }

        std::stringstream ss(line);
        std::string idStr;
        if (!std::getline(ss, idStr, ';'))
        {
            out << line << '\n';
            continue;
        }

        int lineId = 0;
        try { lineId = std::stoi(idStr); }
        catch (...) { out << line << '\n'; continue; }

        if (lineId == id)
        {
            deleted = true;
            continue;
        }

        out << line << '\n';
    }

    in.close();
    out.close();

    if (!deleted)
    {
        std::remove(tempPath.c_str());
        return false;
    }

    std::remove(inputPath.c_str());
    std::rename(tempPath.c_str(), inputPath.c_str());
    return true;
}
// REMOVE FROM BAG
void removeFromBagUI(std::map<int, int>& bag, const std::vector<Product>& inventory);
// PRODUCT SEARCH
void searchUI(const std::vector<Product>& inventory);
// ADD TO BAG
void addToBagUI(const std::vector<Product>& inventory, std::map<int, int>& bag);
//VIEW BAG
void viewBag(const std::map<int, int>& bag, const std::vector<Product>& inventory);

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

    LoadProductsService searchService("../database/products.csv");
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
            const int id = getMaxProductId(products) + 1;

            std::ofstream file("../database/products.csv", std::ios::app);
            if (!file.is_open())
            {
                std::cout << "ERROR: Cannot open products.csv for writing\n";
                return;
            }

            file << '\n' << id << ';' << name << ';' << description << ';' << price << ';' << quantity;

            products.emplace_back(id, name, description, price, quantity);
            std::cout << "Product added successfully!\n";
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
            cout << "Restarting product entry..";
        }
        else
        {
            cout << "Unknown option. Try again.\n";
        }
    }
}

void StoreService::customerMenu(const std::string& username)
{
    int choice = 0;
    std::map<int, int> bag;

    while (true)
    {
        cout << "\n--- Customer Menu ---"
             << "\n1. Search products"
             << "\n2. View products"
             << "\n3. View orders"
             << "\n4. My bag"
             << "\n5. Add to bag"
             << "\n6. Delete from bag"
             << "\n0. Logout"
             << "\nChoice: ";

        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }

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
                OrderService service("../database/orders.csv");
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
            case 4:
                viewBag(bag, products);
                break;
            case 5:
                addToBagUI(products, bag);
                break;
            case 6:
                removeFromBagUI(bag, products);
                break;
            case 0:
                cout << "Logging out...\n";
                return;

            default:
                cout << "Unknown option.\n";
        }
    }
}
// === VIEW BAG ===
void viewBag(const std::map<int, int>& bag, const std::vector<Product>& inventory) {
    if (bag.empty()) {
        std::cout << "\nYour bag is empty.\n";
        return;
    }

    double grandTotal = 0.0;

    std::cout << "\n--- Your Shopping Bag ---\n";
    std::cout << std::left << std::setw(5) << "ID"
              << std::setw(20) << "Name"
              << std::setw(10) << "Qty"
              << std::right << std::setw(10) << "Total" << "\n";
    std::cout << std::string(45, '-') << "\n";

    // Iterate through the map (Key: ID, Value: Quantity)
    for (const auto& [id, quantity] : bag) {
        // Find the product details in inventory
        for (const auto& product : inventory) {
            if (product.getId() == id) {
                double rowTotal = product.getPrice() * quantity;
                grandTotal += rowTotal;

                std::cout << std::left << std::setw(5) << id
                          << std::setw(20) << product.getName().substr(0, 19) // Truncate if too long
                          << std::setw(10) << quantity
                          << std::right << std::fixed << std::setprecision(2)
                          << "$" << std::setw(9) << rowTotal << "\n";
                break; // Product found, move to next item in bag
            }
        }
    }

    std::cout << std::string(45, '-') << "\n";
    std::cout << std::left << std::setw(35) << "GRAND TOTAL:"
              << std::right << "$" << std::setw(9) << grandTotal << "\n";
}


// === ADD TO BAG ===
int getValidInt(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);

        try {
            size_t pos;
            int val = std::stoi(input, &pos);
            if (pos == input.length() && val >= 0) return val;
        } catch (...) {}

        std::cout << "Invalid input. Please enter a positive number.\n";
    }
}

const Product* addToBagLogic(int id, const std::vector<Product>& inventory, std::map<int, int>& bag, int& status) {
    for (const auto& p : inventory) {
        if (p.getId() == id) {
            // Check stock limit
            // bag[id] accesses current qty (defaulting to 0 if not in bag yet)
            if (bag[id] >= p.getQuantity()) {
                status = 2; // Error: Not enough stock
                return &p;  // Return product so UI can show the name
            }

            bag[id]++;
            status = 0; // Success
            return &p;
        }
    }
    status = 1; // Error: ID not found
    return nullptr;
}

void addToBagUI(const std::vector<Product>& inventory, std::map<int, int>& bag) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true) {
        std::cout << "\n--- Add to Bag ---\n";
        int id = getValidInt("Enter product ID to add (0 to back): ");

        if (id == 0) return;

        int status = 0;
        const Product* p = addToBagLogic(id, inventory, bag, status);

        if (status == 0) {
            std::cout << "Success! Added '" << p->getName() << "' to bag.\n";
            std::cout << "Quantity in bag: " << bag[id] << "\n";
        }
        else if (status == 1) {
            std::cout << "Error: Product ID " << id << " does not exist.\n";
        }
        else if (status == 2) {
            std::cout << "Error: Cannot add '" << p->getName() << "'.\n";
            std::cout << "Stock limit reached (" << p->getQuantity() << " available).\n";
        }
    }
}

// === REMOVE FROM BAG ===
int removeFromBagLogic(int id, std::map<int, int>& bag) {
    auto it = bag.find(id);

    // Case 1: ID not in bag
    if (it == bag.end()) {
        return 0;
    }

    // Decrement quantity
    it->second--;

    // Case 2: Quantity hit 0, remove entirely
    if (it->second <= 0) {
        bag.erase(it);
        return 2;
    }

    // Case 3: Just decremented
    return 1;
}


void removeFromBagUI(std::map<int, int>& bag, const std::vector<Product>& inventory) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true) {
        std::cout << "\n--- Remove from Bag ---\n";


        // 1. Auto-exit if bag becomes empty
        if (bag.empty()) {
            std::cout << "Nothing to delete, bag is empty. Returning to menu.\n";
            return;
        }

        // 2. Input
        int id = getValidInt("Enter product ID to remove (0 to back): ");
        if (id == 0) return;

        // 3. Find Name (for display)
        std::string pName = "Unknown Product";
        for (const auto& p : inventory) {
            if (p.getId() == id) {
                pName = p.getName();
                break;
            }
        }

        // 4. Logic & Display
        int result = removeFromBagLogic(id, bag);

        if (result == 0) {
            std::cout << "Error: Product ID " << id << " is not in your bag.\n";
        }
        else if (result == 1) {
            std::cout << "Removed 1 \"" << pName << "\".\n";
            std::cout << "Remaining quantity: " << bag[id] << "\n";
        }
        else if (result == 2) {
            std::cout << "Removed 1 \"" << pName << "\".\n";
            std::cout << "Item removed from bag completely.\n";
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

                if (!deleteProductFromFile(id))
                {
                    cout << "Error: Cannot delete product from file.\n";
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
            OrderService service("../database/orders.csv");
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
        customerMenu(username);
    }
}
