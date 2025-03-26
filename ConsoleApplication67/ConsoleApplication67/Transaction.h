#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Account.h"
#include <string>
#include <ctime>

class Transaction {
private:
    std::string id;
    Account* source;
    Account* target;
    double amount;
    bool isCancelled;
    time_t timestamp;

public:
    Transaction(const std::string& id, Account* source, Account* target, double amount)
        : id(id), source(source), target(target), amount(amount),
        isCancelled(false), timestamp(time(nullptr)) {
    }

    // Добавляем недостающие методы
    std::string getId() const { return id; }
    double getAmount() const { return amount; } // Добавлен getAmount
    bool isCancelled() const { return isCancelled; }
    time_t getTimestamp() const { return timestamp; }

    void execute();
    void cancel();
};

#endif // TRANSACTION_H