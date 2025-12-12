#pragma once
#include <string>

using namespace std;

class StoreUI {
public:
    void run();
private:
    static int readInt();

    static string readString();

    static string readLine();

    void loginMenu();
    void adminMenu();
    void manageProducts();
    void searchProducts();
    void listProducts();
    void manageUsers();
    void manageOrders();

    void customerMenu();
};
