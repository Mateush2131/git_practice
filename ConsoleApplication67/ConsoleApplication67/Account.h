#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Client.h"
#include <string>
#include <vector>

enum class AccountType { DEBIT, DEPOSIT, CREDIT };

class Account {

protected:
    std::string id;
    Client* owner;
    double balance;
    AccountType type;

public:

    Account(const std::string& id, Client* owner, double balance, AccountType type)
        : id(id), owner(owner), balance(balance), type(type) {
    }

    // Добавляем недостающие методы
    virtual ~Account() = default;
    virtual void applyInterest() = 0;
    virtual void applyCommission() = 0;

    std::string getId() const { return id; }
    double getBalance() const { return balance; }
    Client* getClient() const { return owner; }
    AccountType getType() const { return type; } // Добавлен getType

    virtual bool transfer(Account& target, double amount);
    
    
        
        virtual bool withdraw(double amount) = 0;
        virtual bool deposit(double amount) = 0;
        virtual bool transfer(Account& target, double amount) = 0;
        // ...
    
};

#endif // ACCOUNT_H