#include "LoginService.h"
#include <fstream>
#include <sstream>
#include <cctype>

namespace {
    bool parseIsAdmin(const std::string &value) {
        std::string lower;
        lower.reserve(value.size());
        for (char ch: value) {
            lower.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
        return lower == "true";
    }
}

LoginService::LoginService(const std::string &usersFilePath)
    : usersFilePath(usersFilePath) {
}

bool LoginService::login(const std::string &username) {
    bool isAdmin = false;

    std::ifstream file(usersFilePath);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    bool isFirstLine = true;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        if (isFirstLine) {
            isFirstLine = false;
            if (line.rfind("username;", 0) == 0) {
                continue;
            }
        }

        std::stringstream ss(line);
        std::string fileUsername;
        std::string isAdminStr;

        if (!std::getline(ss, fileUsername, ';')) {
            continue;
        }
        if (!std::getline(ss, isAdminStr, ';')) {
            continue;
        }

        if (fileUsername == username) {
            isAdmin = parseIsAdmin(isAdminStr);
            break;
        }
    }

    return isAdmin;
}
