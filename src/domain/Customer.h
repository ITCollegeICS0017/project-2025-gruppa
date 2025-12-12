#pragma once
#include <string>
using namespace std;

class Customer {
private:
    string username;

public:
    explicit Customer(const string& username);

    [[nodiscard]] string getUsername() const;
};
