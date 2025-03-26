#ifndef DEBITACCOUNT_H
#define DEBITACCOUNT_H

#include "Account.h"

class DebitAccount : public Account {
private:
    double interestRate;

public:
    DebitAccount(const std::string& id,
        Client* owner,
        double balance,
        double interestRate);

    // Переопределенные методы
    void applyInterest() override;
    void applyCommission() override;
    bool withdraw(double amount) override;
    bool deposit(double amount) override;
    bool transfer(Account& target, double amount) override;

    double getInterestRate() const;
};

#endif // DEBITACCOUNT_H