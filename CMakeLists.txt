cmake_minimum_required(VERSION 3.16)

project(BankAccountSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(bank
    src/main.cpp
    src/Account.cpp
    src/SavingsAccount.cpp
    src/CurrentAccount.cpp
    src/Bank.cpp
    src/Utils.cpp
)

target_include_directories(bank PRIVATE include)

if(MSVC)
    target_compile_options(bank PRIVATE /W4)
else()
    target_compile_options(bank PRIVATE -Wall -Wextra -Wpedantic)
endif()