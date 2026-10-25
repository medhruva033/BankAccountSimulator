#include "Account.h"

#include <iomanip>
#include <sstream>
#include <stdexcept>

Account::Account(int number, const std::string& name,
                 const std::string& accountPin, double initialBalance)
    : accountNumber(number),
      holderName(name),
      pin(accountPin),
      balance(initialBalance) {}

int Account::getAccountNumber() const {
    return accountNumber;
}

std::string Account::getHolderName() const {
    return holderName;
}

double Account::getBalance() const {
    return balance;
}

bool Account::verifyPin(const std::string& enteredPin) const {
    return pin == enteredPin;
}

void Account::deposit(double amount) {
    if (amount <= 0)
        throw std::invalid_argument("Amount must be greater than zero.");

    balance += amount;
}

double Account::getOverdraftLimit() const {
    return 0.0;
}

std::string Account::serialize() const {
    std::ostringstream output;

    output << accountNumber << '|'
           << getType() << '|'
           << holderName << '|'
           << pin << '|'
           << std::fixed << std::setprecision(2) << balance;

    return output.str();
}