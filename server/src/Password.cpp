/*
** EPITECH PROJECT, 2025
** Dufos
** File description:
** Password
*/

#include "Password.hpp"

#include <sodium.h>

std::string Dufos::Password::hashPassword(const std::string& password)
{
    char hashed[crypto_pwhash_STRBYTES];

    if (crypto_pwhash_str(hashed, password.c_str(), password.size(), crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {
        return "";
    }
    return std::string(hashed);
}

bool Dufos::Password::verifyPassword(const std::string& hashed, const std::string& password)
{
    if (crypto_pwhash_str_verify(hashed.c_str(), password.c_str(), password.size()) == 0) {
        return true;
    }
    return false;
}
