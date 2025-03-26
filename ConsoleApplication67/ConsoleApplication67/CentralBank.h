#ifndef CENTRALBANK_H
#define CENTRALBANK_H

#include <string>
#include <vector>

class Bank;
class Transaction;

class CentralBank {
private:
    std::string name;
    std::vector<Bank*> registeredBanks;

public:
    // ќбъ€вл€ем конструктор
    explicit CentralBank(const std::string& bankName);

    // ћетоды
    void registerBank(Bank* bank);
    void processTransaction(Transaction* transaction);
    std::string getName() const;
};

#endif // CENTRALBANK_H