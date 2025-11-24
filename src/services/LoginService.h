#pragma once

#include <string>

class LoginService {
private:
    std::string usersFilePath;

public:
    explicit LoginService(const std::string& usersFilePath = "src/database/users.csv");

    bool login(const std::string& username);
};
