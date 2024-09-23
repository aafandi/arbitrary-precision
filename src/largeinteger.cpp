#include "largeinteger.h"
#include <iostream>
#include <string>
#include <vector>

// Getter
std::string LargeInteger::get_string_representation() {
    return string_representation;
}
// Setter
void LargeInteger::set_string_representation(std::string s) {
    string_representation = s;
}

// Static Methods

long long int LargeInteger::to_base_ten(std::string s) {
    int *size {nullptr};
    size = new int;
    *size = s.size();

    long long int result {0};

    for (int i = 0; i < *size; i++) {
        result += (((int)s[*size - 1 - i]) - 48) * pow(10, i);
    }

    delete size;

    return result;
}

int LargeInteger::from_char_to_int(char c) {
    return (int)(c) - 48;
}

std::string LargeInteger::string_of_zeroes(int n) {
    std::string result = "";
    for (int i = 0; i < n; i++) {
        result += "0";
    }
    return result;
}

// Overloaded Binary Operators
LargeInteger LargeInteger::operator+(const LargeInteger &rhs) const {
    int *size_1 {nullptr}; // size of the integer with more digits
    size_1 = new int;
    int *size_2 {nullptr}; // size of the integers with less digits
    size_2 = new int;
    std::string *summand_1 {nullptr}; // the string with more digits
    summand_1 = new std::string;
    std::string *summand_2 {nullptr}; // the string with less digits
    summand_2 = new std::string;
    int *carrier {nullptr}; // the variable keeping track of the "carrying" in addition
    carrier = new int;
    std::string result = "";

    // Code block below sets size_1, size_2, summand_1, and summand_2 correctly

    if (string_representation.size() >= rhs.string_representation.size()) {
        *size_1 = string_representation.size();
        *size_2 = rhs.string_representation.size();
        *summand_1 = string_representation;
        *summand_2 = rhs.string_representation;
    } else {
        *size_1 = rhs.string_representation.size();
        *size_2 = string_representation.size();
        *summand_1 = rhs.string_representation;
        *summand_2 = string_representation;
    }

    // Edge cases, use usual addition

   if (*size_1 <= 14 && (*size_2 <= 3)) {
    long long int *sumPtr {nullptr};
    sumPtr = new long long int;

    *sumPtr = to_base_ten(*summand_1) + to_base_ten(*summand_2);
    LargeInteger L = LargeInteger(std::to_string(*sumPtr));
    delete size_1;
    delete size_2;
    delete summand_1;
    delete summand_2;
    delete carrier;
    return L;
   }

   // Assume size_1 >= 15, size_2 >= 4:

   *summand_2 = string_of_zeroes(*size_1 - *size_2) + rhs.string_representation;

    for (int i = 0; i < *size_1; i++) {
        int *sumPtr {nullptr};
        sumPtr = new int;
        *sumPtr = from_char_to_int((*summand_1)[*size_1 - 1 - i]) + from_char_to_int((*summand_2)[*size_1 - 1 - i]) + *carrier;
        if (std::to_string(*sumPtr).size() == 2) {
            result += std::to_string(*sumPtr)[1];
            *carrier = 1;
        } else {
            result += std::to_string(*sumPtr);
            *carrier = 0;
        }
    }

    //if (*carrier == 0) {
        //for (int i = 0; i < (*size_1) - (*size_2); i++) {
            //result += ((*summand_1)[*size_1 - 1 - *size_2 - i]);
        //}
    //}
    

    delete size_1;
    delete size_2;
    delete summand_1;
    delete summand_2;
    delete carrier;

    std::reverse(result.begin(), result.end());

    return LargeInteger(result);
}
