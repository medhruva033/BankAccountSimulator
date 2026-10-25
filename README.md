# Bank Account Simulator (C++)

A console-based banking application built with C++17 and
Object-Oriented Programming principles.

## Features

- Create Savings and Current accounts
- PIN-based login
- Deposit and withdraw money
- Transfer money between accounts
- View transaction history
- Savings account balance validation
- Current account overdraft limit
- Persistent account and transaction records
- Exception handling and input validation

## Concepts

- Object-Oriented Programming
- Inheritance and polymorphism
- Abstract classes and virtual functions
- STL vectors and smart pointers
- File handling and serialization
- Exception handling

## Build and Run

### Windows (G++)

Compile from the project root:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -Iinclude src/main.cpp src/Account.cpp src/SavingsAccount.cpp src/CurrentAccount.cpp src/Bank.cpp src/Utils.cpp -o bank.exe
bank.exe