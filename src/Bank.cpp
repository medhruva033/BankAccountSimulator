#include "Bank.h"
#include "CurrentAccount.h"
#include "SavingsAccount.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace {
const char* ACCOUNTS_FILE = "data/accounts.txt";
const char* TRANSACTIONS_FILE = "data/transactions.txt";
}

Bank::Bank() : nextAccountNumber(1001) {
    loadAccounts();
}

Account* Bank::findAccount(int number) {
    for (auto& account : accounts) {
        if (account->getAccountNumber() == number)
            return account.get();
    }
    return nullptr;
}

const Account* Bank::findAccount(int number) const {
    for (const auto& account : accounts) {
        if (account->getAccountNumber() == number)
            return account.get();
    }
    return nullptr;
}

int Bank::createAccount(const std::string& name,
                        const std::string& accountPin,
                        const std::string& type,
                        double initialDeposit) {
    if (name.empty() || name.find('|') != std::string::npos)
        throw std::invalid_argument("Invalid account holder name.");

    if (accountPin.size() != 4 ||
        accountPin.find_first_not_of("0123456789") !=
            std::string::npos)
        throw std::invalid_argument("PIN must contain 4 digits.");

    if (initialDeposit < 0)
        throw std::invalid_argument("Deposit cannot be negative.");

    if (type != "Savings" && type != "Current")
        throw std::invalid_argument("Invalid account type.");

    int number = nextAccountNumber++;

    if (type == "Savings") {
        accounts.push_back(std::make_unique<SavingsAccount>(
            number, name, accountPin, initialDeposit));
    } else {
        accounts.push_back(std::make_unique<CurrentAccount>(
            number, name, accountPin, initialDeposit));
    }

    saveAccounts();

    recordTransaction(std::to_string(number) +
                      "|Account created|0.00");

    return number;
}

bool Bank::login(int number, const std::string& accountPin) const {
    const Account* account = findAccount(number);
    return account && account->verifyPin(accountPin);
}

void Bank::showAccount(int number) const {
    const Account* account = findAccount(number);

    if (!account)
        throw std::runtime_error("Account not found.");

    std::cout << "\nAccount number : "
              << account->getAccountNumber()
              << "\nHolder name   : " << account->getHolderName()
              << "\nAccount type  : " << account->getType()
              << "\nBalance       : Rs. "
              << std::fixed << std::setprecision(2)
              << account->getBalance() << '\n';

    if (account->getOverdraftLimit() > 0) {
        std::cout << "Overdraft limit: Rs. "
                  << account->getOverdraftLimit() << '\n';
    }
}

void Bank::deposit(int number, double amount) {
    Account* account = findAccount(number);

    if (!account)
        throw std::runtime_error("Account not found.");

    account->deposit(amount);
    saveAccounts();

    recordTransaction(std::to_string(number) +
                      "|Deposit|" + std::to_string(amount));
}

void Bank::withdraw(int number, double amount) {
    Account* account = findAccount(number);

    if (!account)
        throw std::runtime_error("Account not found.");

    account->withdraw(amount);
    saveAccounts();

    recordTransaction(std::to_string(number) +
                      "|Withdrawal|" + std::to_string(amount));
}

void Bank::transfer(int fromNumber, int toNumber, double amount) {
    if (fromNumber == toNumber)
        throw std::invalid_argument(
            "Cannot transfer to the same account.");

    Account* sender = findAccount(fromNumber);
    Account* receiver = findAccount(toNumber);

    if (!sender || !receiver)
        throw std::runtime_error("Account not found.");

    if (amount <= 0)
        throw std::invalid_argument(
            "Transfer amount must be greater than zero.");

    if (amount > sender->getBalance() + sender->getOverdraftLimit())
        throw std::runtime_error("Insufficient funds.");

    // Withdraw first; only credit the receiver if withdrawal succeeds.
    sender->withdraw(amount);

    try {
        receiver->deposit(amount);
    } catch (...) {
        // Restore the sender if the credit operation fails.
        sender->deposit(amount);
        throw;
    }

    saveAccounts();

    recordTransaction(std::to_string(fromNumber) +
        "|Transfer out to " + std::to_string(toNumber) +
        "|" + std::to_string(amount));

    recordTransaction(std::to_string(toNumber) +
        "|Transfer in from " + std::to_string(fromNumber) +
        "|" + std::to_string(amount));
}

void Bank::recordTransaction(const std::string& message) const {
    std::ofstream file(TRANSACTIONS_FILE, std::ios::app);

    if (!file)
        throw std::runtime_error("Cannot open transaction file.");

    file << message << '\n';

    if (!file)
        throw std::runtime_error("Failed to write transaction.");
}

void Bank::showTransactionHistory(int number) const {
    if (!findAccount(number))
        throw std::runtime_error("Account not found.");

    std::ifstream file(TRANSACTIONS_FILE);

    if (!file) {
        std::cout << "No transaction history found.\n";
        return;
    }

    std::cout << "\n--- Transaction History ---\n";

    std::string line;
    bool found = false;

    while (std::getline(file, line)) {
        std::istringstream row(line);
        std::string account, description, amount;

        if (!std::getline(row, account, '|') ||
            !std::getline(row, description, '|') ||
            !std::getline(row, amount)) {
            continue;
        }

        try {
            if (std::stoi(account) == number) {
                std::cout << description
                          << " | Rs. " << amount << '\n';
                found = true;
            }
        } catch (const std::exception&) {
            continue;
        }
    }

    if (!found)
        std::cout << "No transactions recorded yet.\n";
}

void Bank::saveAccounts() const {
    std::ofstream file(ACCOUNTS_FILE);

    if (!file)
        throw std::runtime_error("Cannot save account data.");

    for (const auto& account : accounts)
        file << account->serialize() << '\n';

    if (!file)
        throw std::runtime_error("Failed to save account data.");
}

void Bank::loadAccounts() {
    std::ifstream file(ACCOUNTS_FILE);

    if (!file)
        return;

    std::string line;

    while (std::getline(file, line)) {
        std::istringstream row(line);

        std::string numberText, type, name, accountPin, balanceText;

        if (!std::getline(row, numberText, '|') ||
            !std::getline(row, type, '|') ||
            !std::getline(row, name, '|') ||
            !std::getline(row, accountPin, '|') ||
            !std::getline(row, balanceText)) {
            continue;
        }

        try {
            int number = std::stoi(numberText);
            double balance = std::stod(balanceText);

            if (number <= 0 || balance < 0 || name.empty() ||
                name.find('|') != std::string::npos ||
                accountPin.size() != 4 ||
                accountPin.find_first_not_of("0123456789") !=
                    std::string::npos) {
                continue;
            }

            if (findAccount(number))
                continue;

            if (type == "Savings") {
                accounts.push_back(std::make_unique<SavingsAccount>(
                    number, name, accountPin, balance));
            } else if (type == "Current") {
                accounts.push_back(std::make_unique<CurrentAccount>(
                    number, name, accountPin, balance));
            } else {
                continue;
            }

            if (number >= nextAccountNumber)
                nextAccountNumber = number + 1;

        } catch (const std::exception&) {
            // Ignore malformed records.
        }
    }
}