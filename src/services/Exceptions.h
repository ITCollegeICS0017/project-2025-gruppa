#pragma once
#include <stdexcept>

class FormatError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class BusinessRuleError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class UnknownUserError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};
