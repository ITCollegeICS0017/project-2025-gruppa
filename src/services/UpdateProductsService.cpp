#include "UpdateProductsService.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>

UpdateProductsService::UpdateProductsService(const std::string &dbFilePath)
    : dbFilePath(dbFilePath) {
}

int UpdateProductsService::getNextId() const {
    std::ifstream file(dbFilePath);
    if (!file.is_open()) {
        return 1;
    }

    std::string line;
    bool isFirstLine = true;
    int maxId = 0;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        if (isFirstLine) {
            isFirstLine = false;
            if (!std::isdigit(static_cast<unsigned char>(line[0]))) {
                continue;
            }
        }

        std::stringstream ss(line);
        std::string idStr;

        if (!std::getline(ss, idStr, ';')) {
            continue;
        }

        try {
            const int id = std::stoi(idStr);
            if (id > maxId) {
                maxId = id;
            }
        } catch (...) {
        }
    }

    return maxId + 1;
}

Product UpdateProductsService::addProduct(
    const std::string &name,
    const std::string &description,
    double price,
    int quantity
) {
    bool needHeader = false;

    {
        std::ifstream file(dbFilePath);
        if (!file.is_open() || file.peek() == std::ifstream::traits_type::eof()) {
            needHeader = true;
        }
    }

    const int newId = getNextId();

    std::ofstream out(dbFilePath, std::ios::app);
    if (!out.is_open()) {
        throw std::runtime_error("Cannot open products database file for writing");
    }

    if (needHeader) {
        out << "id;name;description;price;quantity\n";
    }

    out << newId << ';'
            << name << ';'
            << description << ';'
            << price << ';'
            << quantity << '\n';

    return Product(newId, name, description, price, quantity);
}

bool UpdateProductsService::deleteProductById(int id) {
    std::ifstream in(dbFilePath);
    if (!in.is_open()) {
        return false;
    }

    std::string line;
    std::vector<std::string> lines;
    bool isFirstLine = true;
    bool deleted = false;

    while (std::getline(in, line)) {
        if (line.empty()) {
            continue;
        }

        if (isFirstLine) {
            isFirstLine = false;
            if (!std::isdigit(static_cast<unsigned char>(line[0]))) {
                lines.push_back(line);
                continue;
            }
        }

        std::stringstream ss(line);
        std::string idStr;
        if (!std::getline(ss, idStr, ';')) {
            lines.push_back(line);
            continue;
        }

        try {
            const int currentId = std::stoi(idStr);
            if (currentId == id) {
                deleted = true;
                continue;
            }
        } catch (...) {
            lines.push_back(line);
            continue;
        }

        lines.push_back(line);
    }

    in.close();

    if (!deleted) {
        return false;
    }

    std::ofstream out(dbFilePath, std::ios::trunc);
    if (!out.is_open()) {
        return false;
    }

    for (const auto &l: lines) {
        out << l << '\n';
    }

    return true;
}
