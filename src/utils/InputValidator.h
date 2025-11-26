#ifndef PROJECT_2025_GRUPPA_INPUTVALIDATOR_H
#define PROJECT_2025_GRUPPA_INPUTVALIDATOR_H

#pragma once

#include <string>
#include <regex>

class InputValidator {
public:
    static bool isUsernameValid(const std::string &value);

    static bool isProductNameValid(const std::string &value);

    static bool isProductDescriptionValid(const std::string &value);

    static bool isPriceValid(const std::string &value);

    static bool isQuantityValid(const std::string &value);
};

#endif // PROJECT_2025_GRUPPA_INPUTVALIDATOR_H
