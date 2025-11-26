#pragma once
#include <string>

class LoginService {
private:
    std::string usersFilePath;

    bool parseIsAdmin(const std::string &value) const;

    void ensureUsersFile() const;

public:
    explicit LoginService(std::string usersFilePath = "database/users.csv");

    // Checks if username exists; sets isAdmin
    bool userExists(const std::string& username, bool& isAdmin) const;

    // Main login menu
    void loginMenu() const;
};
