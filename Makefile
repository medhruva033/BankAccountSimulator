CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Iinclude

SOURCES = src/main.cpp src/Account.cpp src/SavingsAccount.cpp \
          src/CurrentAccount.cpp src/Bank.cpp src/Utils.cpp

TARGET = bank.exe

all:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	del /Q $(TARGET) 2>NUL