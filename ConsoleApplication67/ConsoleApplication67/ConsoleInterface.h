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
            default: std::cout << "�������� �����\n";
            }
        }
    }

    void displayMenu() {
        std::cout << "\n=== ���������� ������� ===\n";
        std::cout << "1. ������� �������\n";
        std::cout << "2. ������� ����\n";
        std::cout << "3. ��������� ����������\n";
        std::cout << "4. �������� ����������\n";
        std::cout << "5. �������� ���������� � �����\n";
        std::cout << "6. �����\n";
        std::cout << "�������� ��������: ";
    }

    void createClient() {
        std::string firstName, lastName, passportData, address;
        std::cout << "\n--- �������� ������� ---\n";
        std::cout << "������� ���: "; std::cin >> firstName;
        std::cout << "������� �������: "; std::cin >> lastName;
        std::cout << "������� ���������� ������: ";
        std::cin.ignore();
        std::getline(std::cin, passportData);
        std::cout << "������� �����: ";
        std::getline(std::cin, address);

        Client* client = new Client(firstName, lastName, passportData, address);
        clients.push_back(client);
        std::cout << "������ ������� ������!\n";
    }

    void createAccount() {
        if (clients.empty()) {
            std::cout << "������� �������� �������!\n";
            return;
        }

        std::cout << "\n--- �������� ����� ---\n";
        std::cout << "�������� �������:\n";
        for (size_t i = 0; i < clients.size(); ++i) {
            std::cout << i + 1 << ". " << clients[i]->getFullName() << "\n";
        }

        size_t clientChoice;
        std::cin >> clientChoice;
        if (clientChoice < 1 || clientChoice > clients.size()) {
            std::cout << "�������� ����� �������\n";
            return;
        }

        std::cout << "�������� ��� �����:\n";
        std::cout << "1. ���������\n2. ����������\n3. ���������\n";
        int typeChoice;
        std::cin >> typeChoice;

        double initialBalance;
        std::cout << "������� ��������� ������: ";
        std::cin >> initialBalance;

        AccountType type;
        switch (typeChoice) {
        case 1: type = AccountType::DEBIT; break;
        case 2: type = AccountType::DEPOSIT; break;
        case 3: type = AccountType::CREDIT; break;
        default:
            std::cout << "�������� ��� �����\n";
            return;
        }

        // ����� ������ ���� ������ �������� ����� ����� Bank
        // ��� ������� ������� ��������
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
            std::cout << "���� ������� ������! �����: " << account->getId() << "\n";
        }
    }

    void performTransaction() {
        if (accounts.size() < 2) {
            std::cout << "������������ ������ ��� ����������\n";
            return;
        }

        std::cout << "\n--- ���������� ���������� ---\n";
        std::cout << "�������� �������� ����:\n";
        displayAccounts();
        size_t from;
        std::cin >> from;

        std::cout << "�������� ������� ����:\n";
        displayAccounts();
        size_t to;
        std::cin >> to;

        if (from < 1 || from > accounts.size() || to < 1 || to > accounts.size()) {
            std::cout << "�������� ����� �����\n";
            return;
        }

        double amount;
        std::cout << "������� �����: ";
        std::cin >> amount;

        try {
            Transaction* transaction = new Transaction("TR" + std::to_string(transactions.size() + 1),
                accounts[from - 1], accounts[to - 1], amount);
            transaction->execute();
            transactions.push_back(transaction);
            std::cout << "���������� ��������� �������!\n";
        }
        catch (const std::exception& e) {
            std::cout << "������: " << e.what() << "\n";
        }
    }

    void cancelTransaction() {
        if (transactions.empty()) {
            std::cout << "��� ���������� ��� ������\n";
            return;
        }

        std::cout << "\n--- ������ ���������� ---\n";
        std::cout << "�������� ���������� ��� ������:\n";
        for (size_t i = 0; i < transactions.size(); ++i) {
            std::cout << i + 1 << ". " << transactions[i]->getId() << " - "
                << transactions[i]->getAmount() << "\n";
        }

        size_t choice;
        std::cin >> choice;
        if (choice < 1 || choice > transactions.size()) {
            std::cout << "�������� �����\n";
            return;
        }

        try {
            transactions[choice - 1]->cancel();
            std::cout << "���������� �������� �������!\n";
        }
        catch (const std::exception& e) {
            std::cout << "������: " << e.what() << "\n";
        }
    }

    void displayAccountInfo() {
        if (accounts.empty()) {
            std::cout << "��� ��������� ������\n";
            return;
        }

        std::cout << "\n--- ���������� � ������ ---\n";
        displayAccounts();

        size_t choice;
        std::cout << "�������� ���� ��� ���������: ";
        std::cin >> choice;

        if (choice < 1 || choice > accounts.size()) {
            std::cout << "�������� �����\n";
            return;
        }

        Account* account = accounts[choice - 1];
        std::cout << "\n����� �����: " << account->getId()
            << "\n���: " << (account->getType() == AccountType::DEBIT ? "���������" :
                account->getType() == AccountType::DEPOSIT ? "����������" : "���������")
            << "\n������: " << account->getBalance()
            << "\n��������: " << account->getClient()->getFullName() << "\n";
    }

private:
    void displayAccounts() {
        for (size_t i = 0; i < accounts.size(); ++i) {
            std::cout << i + 1 << ". " << accounts[i]->getId() << " ("
                << (accounts[i]->getType() == AccountType::DEBIT ? "���������" :
                    accounts[i]->getType() == AccountType::DEPOSIT ? "����������" : "���������")
                << ") - ������: " << accounts[i]->getBalance() << "\n";
        }
    }
};

#endif 