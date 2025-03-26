#ifndef CONSOLEINTERFACE_H
#define CONSOLEINTERFACE_H

#include "CentralBank.h"
#include "Client.h"
#include "Account.h"
#include "Transaction.h"
#include <iostream>
#include <vector>
#include "ConsoleInterface.h"

class ConsoleInterface {
private:
    CentralBank* centralBank;
    std::vector<Client*> clients;
    std::vector<Account*> accounts;
    std::vector<Transaction*> transactions;

public:
    ConsoleInterface(CentralBank* centralBank) : centralBank(centralBank) {}

    void start() {
        while (true) {
            displayMenu();
            int choice;
            std::cin >> choice;
            switch (choice) {
            case 1: createClient(); break;
            case 2: createAccount(); break;
            case 3: performTransaction(); break;
            case 4: cancelTransaction(); break;
            case 5: displayAccountInfo(); break;
            case 6: return;
            default: std::cout << "Неверный выбор\n";
            }
        }
    }

    void displayMenu() {
        std::cout << "\n=== Банковская система ===\n";
        std::cout << "1. Создать клиента\n";
        std::cout << "2. Создать счет\n";
        std::cout << "3. Выполнить транзакцию\n";
        std::cout << "4. Отменить транзакцию\n";
        std::cout << "5. Показать информацию о счете\n";
        std::cout << "6. Выйти\n";
        std::cout << "Выберите действие: ";
    }

    void createClient() {
        std::string firstName, lastName, passportData, address;
        std::cout << "\n--- Создание клиента ---\n";
        std::cout << "Введите имя: "; std::cin >> firstName;
        std::cout << "Введите фамилию: "; std::cin >> lastName;
        std::cout << "Введите паспортные данные: ";
        std::cin.ignore();
        std::getline(std::cin, passportData);
        std::cout << "Введите адрес: ";
        std::getline(std::cin, address);

        Client* client = new Client(firstName, lastName, passportData, address);
        clients.push_back(client);
        std::cout << "Клиент успешно создан!\n";
    }

    void createAccount() {
        if (clients.empty()) {
            std::cout << "Сначала создайте клиента!\n";
            return;
        }

        std::cout << "\n--- Создание счета ---\n";
        std::cout << "Выберите клиента:\n";
        for (size_t i = 0; i < clients.size(); ++i) {
            std::cout << i + 1 << ". " << clients[i]->getFullName() << "\n";
        }

        size_t clientChoice;
        std::cin >> clientChoice;
        if (clientChoice < 1 || clientChoice > clients.size()) {
            std::cout << "Неверный выбор клиента\n";
            return;
        }

        std::cout << "Выберите тип счета:\n";
        std::cout << "1. Дебетовый\n2. Депозитный\n3. Кредитный\n";
        int typeChoice;
        std::cin >> typeChoice;

        double initialBalance;
        std::cout << "Введите начальный баланс: ";
        std::cin >> initialBalance;

        AccountType type;
        switch (typeChoice) {
        case 1: type = AccountType::DEBIT; break;
        case 2: type = AccountType::DEPOSIT; break;
        case 3: type = AccountType::CREDIT; break;
        default:
            std::cout << "Неверный тип счета\n";
            return;
        }

        // Здесь должна быть логика создания счета через Bank
        // Для примера создаем напрямую
        Account* account = nullptr;
        switch (type) {
        case AccountType::DEBIT:
            account = new DebitAccount("DEB" + std::to_string(accounts.size() + 1),
                clients[clientChoice - 1], initialBalance, 0.05);
            break;
        case AccountType::DEPOSIT:
            account = new DepositAccount("DEP" + std::to_string(accounts.size() + 1),
                clients[clientChoice - 1], initialBalance, 0.1,
                time(nullptr) + 365 * 24 * 3600);
            break;
        case AccountType::CREDIT:
            account = new CreditAccount("CRD" + std::to_string(accounts.size() + 1),
                clients[clientChoice - 1], initialBalance, 1000, 0.02);
            break;
        }

        if (account) {
            accounts.push_back(account);
            std::cout << "Счет успешно создан! Номер: " << account->getId() << "\n";
        }
    }

    void performTransaction() {
        if (accounts.size() < 2) {
            std::cout << "Недостаточно счетов для транзакции\n";
            return;
        }

        std::cout << "\n--- Выполнение транзакции ---\n";
        std::cout << "Выберите исходный счет:\n";
        displayAccounts();
        size_t from;
        std::cin >> from;

        std::cout << "Выберите целевой счет:\n";
        displayAccounts();
        size_t to;
        std::cin >> to;

        if (from < 1 || from > accounts.size() || to < 1 || to > accounts.size()) {
            std::cout << "Неверный выбор счета\n";
            return;
        }

        double amount;
        std::cout << "Введите сумму: ";
        std::cin >> amount;

        try {
            Transaction* transaction = new Transaction("TR" + std::to_string(transactions.size() + 1),
                accounts[from - 1], accounts[to - 1], amount);
            transaction->execute();
            transactions.push_back(transaction);
            std::cout << "Транзакция выполнена успешно!\n";
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    }

    void cancelTransaction() {
        if (transactions.empty()) {
            std::cout << "Нет транзакций для отмены\n";
            return;
        }

        std::cout << "\n--- Отмена транзакции ---\n";
        std::cout << "Выберите транзакцию для отмены:\n";
        for (size_t i = 0; i < transactions.size(); ++i) {
            std::cout << i + 1 << ". " << transactions[i]->getId() << " - "
                << transactions[i]->getAmount() << "\n";
        }

        size_t choice;
        std::cin >> choice;
        if (choice < 1 || choice > transactions.size()) {
            std::cout << "Неверный выбор\n";
            return;
        }

        try {
            transactions[choice - 1]->cancel();
            std::cout << "Транзакция отменена успешно!\n";
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    }

    void displayAccountInfo() {
        if (accounts.empty()) {
            std::cout << "Нет созданных счетов\n";
            return;
        }

        std::cout << "\n--- Информация о счетах ---\n";
        displayAccounts();

        size_t choice;
        std::cout << "Выберите счет для просмотра: ";
        std::cin >> choice;

        if (choice < 1 || choice > accounts.size()) {
            std::cout << "Неверный выбор\n";
            return;
        }

        Account* account = accounts[choice - 1];
        std::cout << "\nНомер счета: " << account->getId()
            << "\nТип: " << (account->getType() == AccountType::DEBIT ? "Дебетовый" :
                account->getType() == AccountType::DEPOSIT ? "Депозитный" : "Кредитный")
            << "\nБаланс: " << account->getBalance()
            << "\nВладелец: " << account->getClient()->getFullName() << "\n";
    }

private:
    void displayAccounts() {
        for (size_t i = 0; i < accounts.size(); ++i) {
            std::cout << i + 1 << ". " << accounts[i]->getId() << " ("
                << (accounts[i]->getType() == AccountType::DEBIT ? "Дебетовый" :
                    accounts[i]->getType() == AccountType::DEPOSIT ? "Депозитный" : "Кредитный")
                << ") - Баланс: " << accounts[i]->getBalance() << "\n";
        }
    }
};

#endif 