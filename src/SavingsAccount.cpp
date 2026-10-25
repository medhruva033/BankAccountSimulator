#include "SavingsAccount.h"

#include <stdexcept>

SavingsAccount::SavingsAccount(
    int number, const std::string& name,
    const std::string& accountPin, double initialBalance)
    : Account(number, name, accountPin, initialBalance) {}

void SavingsAccount::withdraw(double amount) {
    if (amount <= 0)
        throw std::invalid_argument("Amount must be greater than zero.");

    if (amount > balance)
        throw std::runtime_error("Insufficient balance.");

    balance -= amount;
}

std::string SavingsAccount::getType() const {
    return "Savings";
}