//
// Created by iznets on 9/20/25.
//
#include "../../include/entities/Administrator.h"

// constructor
Administrator::Administrator(int i, const std::string& n, const std::string& token, const std::string& rules)
    : id(i), name(n), auth_token(token), discount_rules_ref(rules) {}

// getters
int Administrator::getId() const { return id; }
std::string Administrator::getName() const { return name; }
std::string Administrator::getAuthToken() const { return auth_token; }
std::string Administrator::getDiscountRulesRef() const { return discount_rules_ref; }

// setters
void Administrator::setName(const std::string& n) { name = n; }
void Administrator::setAuthToken(const std::string& token) { auth_token = token; }
void Administrator::setDiscountRulesRef(const std::string& rules) { discount_rules_ref = rules; }

// Placeholder
void Administrator::addProduct(const std::string& name, const std::string& description, double price, int quantity)
{
}

void Administrator::editDiscount(const std::string& customer_username, double discount)
{
}


