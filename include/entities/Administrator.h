//
// Created by iznets on 9/20/25.
//

#ifndef PROJECT_2025_GRUPPA_ADMINISTRATOR_H
#define PROJECT_2025_GRUPPA_ADMINISTRATOR_H

#include <string>
#include <vector>

class Product; // forward declaration
class Customer; // forward declaration

class Administrator {
private:
    int id;
    std::string name;
    std::string auth_token;
    std::string discount_rules_ref;

public:
    Administrator(int i, const std::string& n, const std::string& token, const std::string& rules);

    int getId() const;
    std::string getName() const;
    std::string getAuthToken() const;
    std::string getDiscountRulesRef() const;

    void setName(const std::string& n);
    void setAuthToken(const std::string& token);
    void setDiscountRulesRef(const std::string& rules);

    static void addProduct(const std::string& name, const std::string& description, double price, int quantity);
    static void editDiscount(const std::string& customer_username, double discount);


};

#endif //PROJECT_2025_GRUPPA_ADMINISTRATOR_H