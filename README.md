# Bank Account Simulator (C++)

A console-based banking application built with **C++17** and Object-Oriented Programming (OOP). This project demonstrates account management, banking transactions, inheritance, polymorphism, exception handling, and file-based persistence.

## Features

- Create Savings and Current accounts
- PIN-based account login
- Deposit and withdraw money
- Transfer funds between accounts
- View account details and transaction history
- Validate balances and withdrawal limits
- Support a configurable Current Account overdraft limit
- Save account records between program runs
- Handle invalid input and banking operation errors

## Tech Stack

- **Language:** C++17
- **Compiler:** GCC / G++
- **Data structures:** STL vectors and smart pointers
- **Storage:** Text files
- **Build tools:** G++, CMake, Make

## Concepts Demonstrated

- Object-Oriented Programming
- Encapsulation and abstraction
- Inheritance and polymorphism
- Abstract classes and virtual functions
- Exception handling
- File handling and serialization
- Input validation

## Project Structure

```text
BankAccountSimulator/
├── include/
│   ├── Account.h
│   ├── Bank.h
│   ├── CurrentAccount.h
│   ├── SavingsAccount.h
│   └── Utils.h
├── src/
│   ├── Account.cpp
│   ├── Bank.cpp
│   ├── CurrentAccount.cpp
│   ├── main.cpp
│   ├── SavingsAccount.cpp
│   └── Utils.cpp
├── data/
├── .gitignore
├── CMakeLists.txt
├── Makefile
└── README.md
```

## Build and Run

### Windows (G++)

Compile from the project root:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -Iinclude src/main.cpp src/Account.cpp src/SavingsAccount.cpp src/CurrentAccount.cpp src/Bank.cpp src/Utils.cpp -o bank.exe
```

Run the application:

```cmd
bank.exe
```

### Linux / macOS (G++)

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -Iinclude src/main.cpp src/Account.cpp src/SavingsAccount.cpp src/CurrentAccount.cpp src/Bank.cpp src/Utils.cpp -o bank
./bank
```

## Data Storage

- Account records: `data/accounts.txt`
- Transaction history: `data/transactions.txt`

Run the application from the project root so the relative file paths resolve correctly.

## Future Improvements

- Secure PIN hashing
- Integer-based monetary calculations
- Automated unit tests
- Improved transaction recovery and persistence guarantees
- Database integration
- Transaction timestamps and formatted reports

## Security Disclaimer

This is an educational project, not production banking software. PINs are stored in plaintext, and monetary calculations use `double`. Do not use real banking credentials or financial information.

## Author

**Dhruva M. K.**

GitHub: [@medhruva033](https://github.com/medhruva033)
