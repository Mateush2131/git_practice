#include <iostream>
#include <vector>
#include <string>
#include "Bank.h"
#include "Client.h"
#include "Account.h"
#include "DebitAccount.h"
#include "DepositAccount.h"
#include "CreditAccount.h"
#include "CentralBank.h"
#include "ConsoleInterface.h"
#include "Transaction.h"
#include "AccountType.h"


int main() {
    try {
        
        CentralBank centralBank("National Bank");

     
       
        Bank bank("MyBank", &centralBank);
       
        ConsoleInterface console(&centralBank);
        console.start();

       
        std::cout << "Enter account type (debit/deposit/credit): ";
        std::string input;
        std::cin >> input;

     
        AccountType type = operator"" _accounttype(input.c_str(), input.size());

      
        switch (type) {
        case AccountType::DEBIT:
            std::cout << "Создан дебетовый счет." << std::endl;
            break;
        case AccountType::DEPOSIT:
            std::cout << "Создан депозитный счет." << std::endl;
            break;
        case AccountType::CREDIT:
            std::cout << "Создан кредитный счет." << std::endl;
            break;
        default:
            std::cout << "Неизвестный тип счета." << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}