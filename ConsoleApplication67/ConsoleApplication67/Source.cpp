#include<string>

#include"Client.h"
class Account {
protected:
    std::string accountId; 
    double balance; 
    Client* owner;

public:
   
    Account(const std::string& accountId, Client* owner, double initialBalance)
        : accountId(accountId), owner(owner), balance(initialBalance) {
    }

  
    virtual void deposit(double amount) {
        balance += amount;
    }

    
    virtual void withdraw(double amount) {
        if (amount > balance) {
            throw std::runtime_error("Недостаточно средств на счете");
        }
        balance -= amount;
    }

 
    virtual void transfer(Account* targetAccount, double amount) {
        withdraw(amount); 
        targetAccount->deposit(amount); 
    }

    
    virtual void applyInterest() = 0;

  
    virtual void applyCommission() = 0;

 
    std::string getAccountId() const {
        return accountId;
    }


    double getBalance() const {
        return balance;
    }
};
