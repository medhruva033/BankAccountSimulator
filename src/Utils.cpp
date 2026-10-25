#include "Utils.h"

#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>

int readInt(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        int value;

        if (std::cin >> value) {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        if (std::cin.eof())
            throw std::runtime_error("Input stream closed.");

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Invalid input. Enter a whole number.\n";
    }
}

double readAmount(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        double amount;

        if (std::cin >> amount) {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');

            if (std::isfinite(amount) && amount >= 0)
                return amount;

            std::cout << "Enter a valid non-negative amount.\n";
            continue;
        }

        if (std::cin.eof())
            throw std::runtime_error("Input stream closed.");

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Invalid amount. Try again.\n";
    }
}

std::string readLine(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string value;

        if (!std::getline(std::cin, value))
            throw std::runtime_error("Input stream closed.");

        if (value.find_first_not_of(" \t\r\n") != std::string::npos)
            return value;

        std::cout << "Input cannot be empty.\n";
    }
}

std::string readPin() {
    while (true) {
        std::string pin = readLine("Enter a 4-digit PIN: ");

        if (pin.size() == 4 &&
            pin.find_first_not_of("0123456789") == std::string::npos)
            return pin;

        std::cout << "PIN must contain exactly 4 digits.\n";
    }
}