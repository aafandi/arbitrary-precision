#include "caesar.h"
#include <algorithm>
#include <random>

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

// Encrypted Method

std::string Caesar::encrypt() {
    // Generate a random permutation of upper_case_letters
    std::string encrypted_string = "";
    std::vector<char> upper_case_characters_permuted = upper_case_characters;
    std::vector<char> lower_case_characters_permuted = lower_case_characters;

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(upper_case_characters_permuted.begin(), upper_case_characters_permuted.end(), g);

    for (int i = 0; i < 26; i++) {
        lower_case_characters_permuted[i] = (char)tolower(upper_case_characters_permuted[i]);
    }

    for (auto c: plaintext_string) {
        if (isupper(c)) {
            auto it = find(upper_case_characters_permuted.begin(), upper_case_characters_permuted.end(), c);
            int location = it - upper_case_characters_permuted.begin();
            encrypted_string += upper_case_characters[location];
            continue;
        } else if (islower(c)) {
            auto it = find(lower_case_characters_permuted.begin(), lower_case_characters_permuted.end(), c);
            int location = it - lower_case_characters_permuted.begin();
            encrypted_string += lower_case_characters[location];
            continue;
        } else {
            encrypted_string += c;
        }
    }
    return encrypted_string;
}
