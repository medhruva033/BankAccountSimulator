#include "Bank.h"
#include "Utils.h"

#include <iostream>
#include <stdexcept>
#include <string>

void createAccountMenu(Bank& bank) {
    std::cout << "\n--- Create Account ---\n";

    std::string name = readLine("Account holder name: ");
    std::string pin = readPin();

    std::cout << "1. Savings Account\n"
              << "2. Current Account\n";

    int choice = readInt("Choose account type: ");

    if (choice != 1 && choice != 2) {
        std::cout << "Invalid account type.\n";
        return;
    }

    double amount = readAmount("Initial deposit (Rs.): ");

    std::string type = (choice == 1) ? "Savings" : "Current";

    int number = bank.createAccount(name, pin, type, amount);

    std::cout << "\nAccount created successfully!\n"
              << "Account number: " << number << '\n';
}

void accountMenu(Bank& bank, int number) {
    while (true) {
        std::cout << "\n===== BANK ACCOUNT MENU =====\n"
                  << "1. View account details\n"
                  << "2. Deposit money\n"
                  << "3. Withdraw money\n"
                  << "4. Transfer money\n"
                  << "5. Transaction history\n"
                  << "0. Logout\n";

        int choice = readInt("Enter choice: ");

        try {
            switch (choice) {
                case 1:
                    bank.showAccount(number);
                    break;

                case 2:
                    bank.deposit(
                        number, readAmount("Deposit amount: "));
                    std::cout << "Deposit successful.\n";
                    break;

                case 3:
                    bank.withdraw(
                        number, readAmount("Withdrawal amount: "));
                    std::cout << "Withdrawal successful.\n";
                    break;

                case 4: {
                    int destination =
                        readInt("Destination account number: ");

                    double amount =
                        readAmount("Transfer amount: ");

                    bank.transfer(number, destination, amount);
                    std::cout << "Transfer successful.\n";
                    break;
                }

                case 5:
                    bank.showTransactionHistory(number);
                    break;

                case 0:
                    std::cout << "Logged out.\n";
                    return;

                default:
                    std::cout << "Invalid menu choice.\n";
            }
        } catch (const std::exception& error) {
            std::cout << "Operation failed: "
                      << error.what() << '\n';
        }
    }
}

void loginMenu(Bank& bank) {
    std::cout << "\n--- Account Login ---\n";

    int number = readInt("Account number: ");
    std::string pin = readPin();

    if (!bank.login(number, pin)) {
        std::cout << "Invalid account number or PIN.\n";
        return;
    }

    std::cout << "Login successful.\n";
    accountMenu(bank, number);
}

int main() {
    try {
        Bank bank;

        while (true) {
            std::cout << "\n================================\n"
                      << "     BANK ACCOUNT SIMULATOR\n"
                      << "================================\n"
                      << "1. Create account\n"
                      << "2. Login\n"
                      << "0. Exit\n";

            int choice = readInt("Enter choice: ");

            try {
                switch (choice) {
                    case 1:
                        createAccountMenu(bank);
                        break;

                    case 2:
                        loginMenu(bank);
                        break;

                    case 0:
                        std::cout << "Thank you for using the simulator.\n";
                        return 0;

                    default:
                        std::cout << "Invalid menu choice.\n";
                }
            } catch (const std::exception& error) {
                std::cout << "Error: " << error.what() << '\n';
            }
        }
    } catch (const std::exception& error) {
        std::cerr << "Fatal error: " << error.what() << '\n';
        return 1;
    }
}