#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
protected:
    int accountNumber;
    std::string holderName;
    std::string pin;
    double balance;

public:
    Account(int number, const std::string& name,
            const std::string& pin, double balance);

    virtual ~Account() = default;

    int getAccountNumber() const;
    std::string getHolderName() const;
    double getBalance() const;

    bool verifyPin(const std::string& enteredPin) const;
    void deposit(double amount);

    virtual void withdraw(double amount) = 0;
    virtual std::string getType() const = 0;
    virtual double getOverdraftLimit() const;

    std::string serialize() const;
};

#endif