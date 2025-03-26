#include "CentralBank.h"
#include "Bank.h"
#include "Transaction.h"

CentralBank::CentralBank(const std::string& bankName)
    : name(bankName) {
}

void CentralBank::registerBank(Bank* bank) {
    registeredBanks.push_back(bank);
}

void CentralBank::processTransaction(Transaction* transaction) {
    // Реализация обработки транзакции
}

std::string CentralBank::getName() const {
    return name;
}