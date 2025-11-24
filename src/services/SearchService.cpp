#include "SearchService.h"
#include <fstream>
#include <sstream>


namespace {
    std::string toLower(const std::string &value) {
        std::string result;
        result.reserve(value.size());
        for (char ch: value) {
            result.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
        return result;
    }

    bool containsCaseInsensitive(const std::string &text, const std::string &pattern) {
        const std::string textLower = toLower(text);
        const std::string patternLower = toLower(pattern);
        return textLower.find(patternLower) != std::string::npos;
    }

    bool parseProductLine(const std::string &line, Product &product) {
        if (line.empty()) {
            return false;
        }

        std::stringstream ss(line);
        std::string idStr;
        std::string name;
        std::string description;
        std::string priceStr;
        std::string quantityStr;

        if (!std::getline(ss, idStr, ';')) {
            return false;
        }
        if (!std::getline(ss, name, ';')) {
            return false;
        }
        if (!std::getline(ss, description, ';')) {
            return false;
        }
        if (!std::getline(ss, priceStr, ';')) {
            return false;
        }
        if (!std::getline(ss, quantityStr, ';')) {
            return false;
        }

        try {
            const int id = std::stoi(idStr);
            const double price = std::stod(priceStr);
            const int quantity = std::stoi(quantityStr);

            product = Product(id, name, description, price, quantity);
            return true;
        } catch (...) {
            return false;
        }
    }
}

SearchService::SearchService(const std::string &dbFilePath)
    : dbFilePath(dbFilePath) {
}

std::vector<Product> SearchService::loadAll() const {
    std::vector<Product> result;
    std::ifstream file(dbFilePath);
    if (!file.is_open()) {
        return result;
    }

    std::string line;
    bool isFirstLine = true;

    while (std::getline(file, line)) {
        if (isFirstLine) {
            isFirstLine = false;
            if (!line.empty() && !std::isdigit(static_cast<unsigned char>(line[0]))) {
                continue;
            }
        }

        Product product(0, "", "", 0.0, 0);
        if (parseProductLine(line, product)) {
            result.push_back(product);
        }
    }

    return result;
}

std::optional<Product> SearchService::findById(int id) const {
    const std::vector<Product> products = loadAll();
    for (const auto &product: products) {
        if (product.getId() == id) {
            return product;
        }
    }
    return std::nullopt;
}

std::vector<Product> SearchService::findByKeyword(const std::string &keyword) const {
    std::vector<Product> matches;
    if (keyword.empty()) {
        return matches;
    }

    const std::vector<Product> products = loadAll();
    for (const auto &product: products) {
        if (containsCaseInsensitive(product.getName(), keyword)
            || containsCaseInsensitive(product.getDescription(), keyword)) {
            matches.push_back(product);
        }
    }

    return matches;
}

std::vector<Product> SearchService::findByPriceRange(
    std::optional<double> minPrice,
    std::optional<double> maxPrice
) const {
    std::vector<Product> matches;
    const std::vector<Product> products = loadAll();

    for (const auto &product: products) {
        const double price = product.getPrice();

        if (minPrice.has_value() && price < minPrice.value()) {
            continue;
        }
        if (maxPrice.has_value() && price > maxPrice.value()) {
            continue;
        }

        matches.push_back(product);
    }

    return matches;
}
