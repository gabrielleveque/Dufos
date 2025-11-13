
#include "Account.hpp"

#include <iostream>

std::optional<Dufos::Account::Info> Dufos::Account::connectTo()
{
    Info info;
    std::string input;
    bool validAction = false;

    while (!validAction) {
        if (input != "y" && input != "Y" && input != "n" && input != "N") {
            std::cout << "Already have an account? (y/n): ";
            if (std::getline(std::cin, input).eof()) {
                return std::nullopt;
            }
            continue;
        }
        info.action = (input == "y" || input == "Y") ? Action::LOGIN : Action::REGISTER;
        validAction = true;
    }
    if (!getName(info) || !getPassword(info)) {
        return std::nullopt;
    }
    return info;
}

bool Dufos::Account::getName(Info& info)
{
    std::cout << "Enter account name: ";
    if (std::getline(std::cin, info.name).eof()) {
        return false;
    }
    return true;
}

bool Dufos::Account::getPassword(Info& info)
{
    if (info.action == Action::REGISTER) {
        bool passwordsMatch = false;
        std::string passwordToConfirm;
        std::string passwordConfirm;

        while (!passwordsMatch) {
            std::cout << "Enter account password: ";
            if (std::getline(std::cin, passwordToConfirm).eof()) {
                return false;
            }
            std::cout << "Confirm account password: ";
            if (std::getline(std::cin, passwordConfirm).eof()) {
                return false;
            }
            if (passwordToConfirm == passwordConfirm) {
                info.password = passwordToConfirm;
                passwordsMatch = true;
            } else {
                std::cout << "Passwords do not match. Please try again." << std::endl;
            }
        }
    } else {
        std::cout << "Enter account password: ";
        if (std::getline(std::cin, info.password).eof()) {
            return false;
        }
    }
    return true;
}
