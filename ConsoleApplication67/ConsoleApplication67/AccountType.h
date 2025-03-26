#pragma once
// AccountType.h
#ifndef ACCOUNTTYPE_H
#define ACCOUNTTYPE_H

#include <string>
#include <stdexcept>

enum class AccountType { DEBIT, DEPOSIT, CREDIT };

// Объявление оператора
AccountType operator"" _accounttype(const char* str, size_t size);
// AccountType.cpp
#include "AccountType.h"

AccountType operator"" _accounttype(const char* str, size_t size) {
    std::string type(str, size);
    if (type == "debit") return AccountType::DEBIT;
    if (type == "deposit") return AccountType::DEPOSIT;
    if (type == "credit") return AccountType::CREDIT;
    throw std::invalid_argument("Unknown account type: " + type);
}
#endif // ACCOUNTTYPE_H