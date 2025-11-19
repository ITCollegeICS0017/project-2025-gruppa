#include "LoginService.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include "../domain/Administrator.h"
#include "../domain/Customer.h"
#include "AdminService.h"
#include "CustomerService.h"
#include "../utils/InputValidator.h"

void LoginService::loginMenu() {
    while (true) {
        std::string username;
        std::cout << "Enter your username: ";
        std::cin >> username;

        try {
            if (!InputValidator::isUsernameValid(username)) {
                throw std::invalid_argument(
                    "Invalid username. Use only Latin letters and digits, no spaces."
                );
            }

            if (username == "admin") {
                Administrator admin("admin");
                AdminService service;
                service.adminMenu();
            } else {
                Customer customer(username);
                CustomerService service;
                service.customerMenu();
            }

            break;
        } catch (const std::invalid_argument &ex) {
            std::cout << "Login error: " << ex.what() << '\n';
        }
    }
}
