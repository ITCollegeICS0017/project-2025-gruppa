#include "InputValidator.h"

namespace {
    const std::regex usernameRegex(R"(^[A-Za-z0-9]+$)");

    // name: letters/digits/space/dash, <= 30 chars
    const std::regex productNameRegex(R"(^[A-Za-z0-9 \-]{1,30}$)");

    // description: letters/digits/space/dash/comma/dot, <= 30 chars
    const std::regex productDescriptionRegex(R"(^[A-Za-z0-9 \-.,]{1,30}$)");

    // price: numbers only, optional . with 1–2 digits
    const std::regex priceRegex(R"(^[0-9]+(\.[0-9]{1,2})?$)");

    // quantity: integer > 0
    const std::regex quantityRegex(R"(^[1-9][0-9]*$)");
}

bool InputValidator::isUsernameValid(const std::string &value) {
    return std::regex_match(value, usernameRegex);
}

bool InputValidator::isProductNameValid(const std::string &value) {
    return std::regex_match(value, productNameRegex);
}

bool InputValidator::isProductDescriptionValid(const std::string &value) {
    return std::regex_match(value, productDescriptionRegex);
}

bool InputValidator::isPriceValid(const std::string &value) {
    return std::regex_match(value, priceRegex);
}

bool InputValidator::isQuantityValid(const std::string &value) {
    return std::regex_match(value, quantityRegex);
}
