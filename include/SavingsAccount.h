#ifndef SAVINGS_ACCOUNT_H
#define SAVINGS_ACCOUNT_H

#include "Account.h"

class SavingsAccount : public Account {
public:
    SavingsAccount(int number, const std::string& name,
                   const std::string& pin, double balance);

    void withdraw(double amount) override;
    std::string getType() const override;
};

#endif