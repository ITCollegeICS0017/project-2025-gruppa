#include "services/LoginService.h"
#include <iostream>

using namespace std;

int main() {
    try {
        // CLion default working directory
        const LoginService login("CLionProjects/project-2025-gruppa/database/users.csv");
        login.loginMenu();
    } catch (const exception& ex) {
        cout << "Fatal error: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}
