#ifndef CURRENT_ACCOUNT_H
#define CURRENT_ACCOUNT_H

#include "Account.h"

class CurrentAccount : public Account {
public:
    CurrentAccount(int number, const std::string& name,
                   const std::string& pin, double balance);

    void withdraw(double amount) override;
    std::string getType() const override;
    double getOverdraftLimit() const override;
};

#endif