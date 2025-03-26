#ifndef BANK_H
#define BANK_H

#include <vector>
#include <string>
#include "Client.h"
#include "Account.h"
#include "DebitAccount.h"
#include "DepositAccount.h"
#include "CreditAccount.h"
#include "CentralBank.h"
#include "Transaction.h"
#include "account_utils.cpp"  // Для generateAccountId()

enum class AccountType {
    DEBIT,
    DEPOSIT,
    CREDIT
};

class Bank {
private:
    std::string name;
    std::vector<Client*> clients;
    std::vector<Account*> accounts;
    CentralBank* centralBank;

public:
    Bank(const std::string& name, CentralBank* cb);
    // Конструктор с указателем на CentralBank
    Bank(const std::string& bankName, CentralBank* cb)
        : name(bankName), centralBank(cb) {
    }

    // Запрещаем копирование
    Bank(const Bank&) = delete;
    Bank& operator=(const Bank&) = delete;

    // Деструктор для очистки памяти
    ~Bank() {
        for (auto account : accounts) {
            delete account;
        }
        for (auto client : clients) {
            delete client;
        }
    }

    void addClient(Client* client) {
        clients.push_back(client);
    }

    void createAccount(Client* client, AccountType type, double initialBalance) {
        std::string accountId = generateAccountId();
        Account* account = nullptr;

        switch (type) {
        case AccountType::DEBIT:
            account = new DebitAccount(accountId, client, initialBalance, 0.05);
            break;
        case AccountType::DEPOSIT:
            account = new DepositAccount(accountId, client, initialBalance, 0.1,
                time(nullptr) + 365 * 24 * 3600);
            break;
        case AccountType::CREDIT:
            account = new CreditAccount(accountId, client, initialBalance, 1000, 0.02);
            break;
        default:
            throw std::invalid_argument("Unknown account type");
        }

        if (account) {
            accounts.push_back(account);
        }
    };

    void processTransactions() {
        for (auto account : accounts) {
            account->applyInterest();
            account->applyCommission();
        }
    }

    void notifyCentralBank(Transaction* transaction) {
        if (centralBank) {
            centralBank->processTransaction(transaction);
        }
    }

    // Геттеры
    std::string getName() const { return name; }
    const std::vector<Account*>& getAccounts() const { return accounts; }
    const std::vector<Client*>& getClients() const { return clients; }
};

#endif // BANK_H