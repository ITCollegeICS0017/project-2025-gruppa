#include "LoginService.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include "../domain/Administrator.h"
#include "../domain/Customer.h"
#include "AdminService.h"
#include "CustomerService.h"
#include "../utils/InputValidator.h"
using namespace std;


void LoginService::loginMenu()
{
    while (true)
    {
        string username;
        cout << "Enter your username: ";
        cin >> username;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            throw InvalidInput{"format"};
        }

        try
        {
            if (!InputValidator::isUsernameValid(username))
            {
                throw invalid_argument(
                    "Invalid username. Use only Latin letters and digits, no spaces."
                );
            }

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

            break;
        }
        catch (const invalid_argument& ex)
        {
            cout << "Login error: " << ex.what() << '\n';
        }
    }
}
