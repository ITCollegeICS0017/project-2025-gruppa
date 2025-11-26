#include "StoreUI.h"
#include "LoginService.h"
#include "Exceptions.h"
#include <iostream>

using namespace std;

int StoreUI::readInt() {
    int x;
    cin >> x;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        throw FormatError{"Invalid number format"};
    }
    return x;
}

string StoreUI::readString() {
    string s;
    cin >> s;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        throw FormatError{"Invalid text format"};
    }
    return s;
}

string StoreUI::readLine() {
    string s;
    getline(cin, s);
    if (s.empty())
        throw FormatError{"Input cannot be empty"};
    return s;
}

// LOGIN MENU
void StoreUI::loginMenu() {
    cout << "\nWelcome to GRUPPA STORE!\n";
    LoginService loginService;
    loginService.loginMenu();
}

// ADMIN MENU
void StoreUI::adminMenu() {
    while (true) {
        cout << "\n=== ADMIN MENU ===\n";
        cout << "1. Manage products\n";
        cout << "2. Manage orders\n";
        cout << "3. Manage users\n";
        cout << "4. Log out\n";
        cout << "Choose option: ";

        try {
            int option = readInt();
            switch (option) {
                case 1: manageProducts(); break;
                case 2: manageOrders(); break;
                case 3: manageUsers(); break;
                case 4:
                    cout << "Logging out...\n";
                    return;
                default:
                    cout << "Unknown option. Try again.\n";
            }
        } catch (const FormatError &e) {
            cout << e.what() << "\n";
        }
    }
}

// MANAGE PRODUCTS
void StoreUI::manageProducts() {
    while (true) {
        cout << "\n=== MANAGE PRODUCTS ===\n";
        cout << "1. Search by name\n";
        cout << "2. List all\n";
        cout << "3. Go back\n";
        cout << "4. Log out\n";
        cout << "Choose option: ";

        try {
            int option = readInt();
            switch (option) {
                case 1: searchProducts(); break;
                case 2: listProducts(); break;
                case 3: adminMenu(); return;
                case 4:
                    cout << "Logging out...\n";
                    return;
                default:
                    cout << "Unknown option. Try again.\n";
            }
        } catch (const FormatError &e) {
            cout << e.what() << "\n";
        }
    }
}

// PLACEHOLDER FUNCTIONS
void StoreUI::manageOrders() {
    cout << "[Manage orders feature not implemented yet]\n";
}
void StoreUI::manageUsers() {
    cout << "[Manage users feature not implemented yet]\n";
}
void StoreUI::searchProducts() {
    cout << "[Search products feature not implemented yet]\n";
}
void StoreUI::listProducts() {
    cout << "[List products feature not implemented yet]\n";
}
