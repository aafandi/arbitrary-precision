#include "caesar.h"

// Getters

std::string Caesar::get_plaintext_string() {
    return plaintext_string;
}

std::vector<char> Caesar::get_punctuation_characters() {
    return punctuation_characters;
}

std::vector<char> Caesar::get_integer_characters() {
    return integer_characters;
}

std::vector<char> Caesar::get_upper_case_characters() {
    return upper_case_characters;
}

std::vector<char> Caesar::get_lower_case_characters() {
    return lower_case_characters;
}

// Setters

void Caesar::set_plaintext_string(std::string s) {
    plaintext_string = s;
}