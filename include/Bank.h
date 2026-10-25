#ifndef BANK_H
#define BANK_H

#include "Account.h"

#include <memory>
#include <string>
#include <vector>

class Bank {
private:
    std::vector<std::unique_ptr<Account>> accounts;
    int nextAccountNumber;

    Account* findAccount(int number);
    const Account* findAccount(int number) const;

    void saveAccounts() const;
    void loadAccounts();
    void recordTransaction(const std::string& message) const;

public:
    Bank();

    int createAccount(const std::string& name,
                      const std::string& pin,
                      const std::string& type,
                      double initialDeposit);

    bool login(int number, const std::string& pin) const;

    void showAccount(int number) const;
    void deposit(int number, double amount);
    void withdraw(int number, double amount);
    void transfer(int from, int to, double amount);
    void showTransactionHistory(int number) const;
};

#endif