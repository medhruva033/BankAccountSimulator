#include "CurrentAccount.h"

#include <stdexcept>

CurrentAccount::CurrentAccount(
    int number, const std::string& name,
    const std::string& accountPin, double initialBalance)
    : Account(number, name, accountPin, initialBalance) {}

void CurrentAccount::withdraw(double amount) {
    if (amount <= 0)
        throw std::invalid_argument("Amount must be greater than zero.");

    if (amount > balance + getOverdraftLimit())
        throw std::runtime_error("Overdraft limit exceeded.");

    balance -= amount;
}

std::string CurrentAccount::getType() const {
    return "Current";
}

double CurrentAccount::getOverdraftLimit() const {
    return 1000.0;
}