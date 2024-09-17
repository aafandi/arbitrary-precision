#include "caesar.h"

// Getter

std::string caesar::getEncryptedString() {
    return encryptedString;
}

// Setter

void caesar::setEncryptedString(std::string s) {
    encryptedString = s;
}