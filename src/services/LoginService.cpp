#include "LoginService.h"
#include <iostream>
#include <string>
#include "../domain/Administrator.h"
#include "../domain/Customer.h"
#include "AdminService.h"
#include "CustomerService.h"

void LoginService::loginMenu()
{
    std::string username;
    std::cout << "Enter your username: ";
    std::cin >> username;

    if (username == "admin")
    {
        Administrator admin("admin");
        AdminService service;
        service.adminMenu();
    }
    else
    {
        Customer customer(username);
        CustomerService service;
        service.customerMenu();
    }
}
