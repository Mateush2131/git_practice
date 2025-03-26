// DepositAccount.h
#pragma once
#ifndef DEPOSITACCOUNT_H
#define DEPOSITACCOUNT_H

#include "Account.h"
#include <ctime>

class DepositAccount : public Account {
private:
    double interestRate;
    time_t endDate;

public:
    DepositAccount(const std::string& id,
        Client* owner,
        double balance,
        double interestRate,
        time_t endDate);

    // Корректные переопределения методов базового класса
    void applyInterest() override;
    void applyCommission() override;
    bool withdraw(double amount) override;
    bool deposit(double amount) override;
    bool transfer(Account& target, double amount) override;

    // Геттеры
    double getInterestRate() const;
    time_t getEndDate() const;
};

#endif // DEPOSITACCOUNT_H