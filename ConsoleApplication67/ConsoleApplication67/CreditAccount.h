#ifndef CREDITACCOUNT_H
#define CREDITACCOUNT_H

#include "Account.h"
#include <stdexcept>

class CreditAccount : public Account {
private:
    double creditLimit;
    double commissionRate;

public:
    CreditAccount(const std::string& id,
        Client* owner,
        double balance,
        double creditLimit,
        double commissionRate);

    // Реализация всех чисто виртуальных методов
    void applyInterest() override;
    void applyCommission() override;
    bool withdraw(double amount) override;
    bool deposit(double amount) override;
    bool transfer(Account& target, double amount) override;

    // Геттеры
    double getCreditLimit() const;
    double getCommissionRate() const;
};

#endif // CREDITACCOUNT_H