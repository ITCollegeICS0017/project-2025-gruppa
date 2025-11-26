#include "LoginService.h"
#include "../StoreService.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <utility>

using namespace std;

// Converts "true"/"false" to bool
bool LoginService::parseIsAdmin(const std::string &value) const {
    string lower;
    lower.reserve(value.size());
    for (char ch: value) {
        lower.push_back(static_cast<char>(tolower(static_cast<unsigned char>(ch))));
    }
    return lower == "true";
}

// Throws if users file cannot be opened
void LoginService::ensureUsersFile() const {
    ifstream file(usersFilePath);
    if (!file.is_open()) {
        throw runtime_error("Cannot open users file at: " + usersFilePath);
    }
}

LoginService::LoginService(std::string usersFilePath)
        : usersFilePath(std::move(usersFilePath)) {}

// Reads users.csv and checks if username exists
bool LoginService::userExists(const std::string& username, bool& isAdmin) const {
    ensureUsersFile(); // throws if file cannot be opened

    ifstream file(usersFilePath);
    string line;
    bool isFirstLine = true;

    while (getline(file, line)) {
        if (line.empty()) continue;

        if (isFirstLine) {
            isFirstLine = false;
            if (line.rfind("username;", 0) == 0)
                continue; // skip CSV header
        }

        stringstream ss(line);
        string fileUsername, isAdminStr;
        getline(ss, fileUsername, ';');
        getline(ss, isAdminStr, ';');

        if (fileUsername == username) {
            isAdmin = parseIsAdmin(isAdminStr);
            return true;
        }
    }
    return false;
}

// Login menu: asks for username, launches admin or customer menus
void LoginService::loginMenu() const {
    while (true) {
        cout << "\n--- LOGIN MENU ---\n";
        cout << "Enter your username: ";
        string username;
        cin >> username;

        bool isAdmin = false;

        try {
            if (!userExists(username, isAdmin)) {
                cout << "User not found. Try again.\n";
                continue;
            }
        } catch (const exception& ex) {
            cout << "Error during login: " << ex.what() << "\n";
            return; // exit program
        }

        StoreService store;

        if (isAdmin) {
            cout << "Welcome, admin.\n";
            store.adminMenu();
        } else {
            cout << "Welcome, " << username << ".\n";
            store.customerMenu();
        }

        break; // exit after logout
    }
}
