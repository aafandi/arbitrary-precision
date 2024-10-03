#include "largeinteger.h"
#include "randomrationals.h"
#include "rational.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Getter
std::string LargeInteger::get_string_representation() {
    return string_representation;
}
// Setter
void LargeInteger::set_string_representation(std::string s) {
    string_representation = s;
}

// Methods to Determine Sign

bool LargeInteger::is_neg() {
    if (string_representation[0] == '-') {
        return true;
    } else {
        return false;
    }
}

bool LargeInteger::is_non_neg() {
    if (string_representation[0] != '-') {
        return true;
    } else {
        return false;
    }
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

std::string LargeInteger::no_leading_zeroes(std::string s) {
    std::string result = s;

    while (result[0] == '0') {
        result = result.substr(1);
    }

    return result;
}

std::vector<LargeInteger> LargeInteger::quotient(LargeInteger L1, LargeInteger L2) {
    // Assume L1 >= L2, and that their number of digits differ by at most 1.
    // This function returns the vector (quotient, remainder)

    std::vector<LargeInteger> result {};

    std::string *quotient_string {nullptr};
    quotient_string = new std::string;

    int *quotient_numerical {nullptr};
    quotient_numerical = new int;

    int *q_hat {nullptr};
    q_hat = new int;

    int *q_hat_calc {nullptr};
    q_hat_calc = new int;

    std::string *remainder {nullptr};
    remainder = new std::string;

    int *size_1 {nullptr};
    size_1 = new int;
    *size_1 = L1.string_representation.size();

    int *size_2 {nullptr};
    size_2 = new int;
    *size_2 = L2.string_representation.size();

    bool *same_number_of_digits {nullptr};
    same_number_of_digits = new bool;
    *same_number_of_digits = (L1.string_representation.size() == L2.string_representation.size());

    bool *one_more_digit {nullptr};
    one_more_digit = new bool;
    *one_more_digit = (L1.string_representation.size() == L2.string_representation.size() + 1);

    int *first_digit_L1 {nullptr};
    first_digit_L1 = new int;
    *first_digit_L1 = from_char_to_int(L1.string_representation[0]);

    int *second_digit_L1 {nullptr};
    second_digit_L1 = new int;
    // don't initialize the value of the above pointer, since it's not guaranteeed to exist (yet)

    int *first_digit_L2 {nullptr};
    first_digit_L2 = new int;
    *first_digit_L2 = from_char_to_int(L2.string_representation[0]);

    std::string *intermediate_numerator {nullptr};
    intermediate_numerator = new std::string;

    std::string *intermediate_remainder {nullptr};
    intermediate_remainder = new std::string;

    // Throw error if inputs are not compatible:

    if ((L1 < L2) || (*size_1 - *size_2 > 1)) {
        std::cerr << "Inputs are not compatible" << std::endl;
        return result;
    }

    // Edge Cases (one digit each, or the same number)

    if ((*size_1 == 1) && (*size_2 == 2)) {
        *quotient_string = std::to_string(*first_digit_L1 / *first_digit_L2);
        *remainder = std::to_string(*first_digit_L1 - *first_digit_L2);
        result.push_back(LargeInteger(*quotient_string));
        result.push_back(LargeInteger(*remainder));
        return result;
    } else if (L1 == L2) {
        *quotient_string = "1";
        *remainder = "0";
        result.push_back(LargeInteger(*quotient_string));
        result.push_back(LargeInteger(*remainder));
        return result;
    }

    // Can now assume that L1 > L2.

    *intermediate_numerator = L1.string_representation.substr(0, *size_2);

    if (*same_number_of_digits) {
        *quotient_numerical = *first_digit_L1 / *first_digit_L2;
        *quotient_string = std::to_string(*quotient_numerical);
        while ((LargeInteger(*quotient_string) * L2) > L1) {
            *quotient_numerical -= 1;
            *quotient_string = std::to_string(*quotient_numerical);
        }
        *remainder = (L1 - (LargeInteger(*quotient_string) * L2)).string_representation;
        result.push_back(LargeInteger(*quotient_string));
        result.push_back(LargeInteger(*remainder));
    } else if ((*one_more_digit) && (L2 <= LargeInteger(*intermediate_numerator))) {
        // Deal with the case when the quotient is a two digit number:
        *quotient_string = quotient(LargeInteger(*intermediate_numerator), L2)[0].string_representation;
        if (quotient(LargeInteger(*intermediate_numerator), L2)[1].string_representation == "0") {
            *intermediate_remainder = L1.string_representation[*size_1 - 1];
        } else {
            *intermediate_remainder = quotient(LargeInteger(*intermediate_numerator), L2)[1].string_representation + L1.string_representation[*size_1 - 1];
        }
        if (L2 > LargeInteger(*intermediate_remainder)) {
            *quotient_string += "0";
            *remainder = *intermediate_remainder;
            result.push_back(LargeInteger(*quotient_string));
            result.push_back(LargeInteger(*remainder));
        } else {
            *quotient_string += quotient(LargeInteger(*intermediate_remainder), L2)[0].string_representation;
            *remainder = quotient(LargeInteger(*intermediate_remainder), L2)[1].string_representation;
            result.push_back(LargeInteger(*quotient_string));
            result.push_back(LargeInteger(*remainder));
        }
        
    } else if ((*one_more_digit) && (L2 > LargeInteger(*intermediate_numerator))) {
        // q_hat is the candidate quotient, it can be off by at most 2 from the real quotient, see Knuth's Algorithm D
        *second_digit_L1 = from_char_to_int(L1.string_representation[1]);
        *q_hat_calc = (((*first_digit_L1) * 10) + (*second_digit_L1)) / ((*first_digit_L2));
        *q_hat = std::min(*q_hat_calc, 9);
        while ((L2 * LargeInteger(std::to_string(*q_hat))) > L1) {
            *q_hat -= 1;
        }
        *quotient_string = std::to_string(*q_hat);
        *remainder = (L1 - (LargeInteger(*quotient_string) * L2)).string_representation;
        result.push_back(LargeInteger(*quotient_string));
        result.push_back(LargeInteger(*remainder));
    }

    delete quotient_string;
    delete quotient_numerical;
    delete q_hat;
    delete q_hat_calc;
    delete remainder;
    delete size_1;
    delete size_2;
    delete same_number_of_digits;
    delete one_more_digit;
    delete first_digit_L1;
    delete first_digit_L2;
    delete intermediate_numerator;
    delete intermediate_remainder;

    return result;
}

std::vector<LargeInteger> LargeInteger::long_division(LargeInteger L1, LargeInteger L2) {
    // This computes L1 / L2, and returns the vector (quotient, remainder)

    std::vector<LargeInteger> result {};

    int *size_1 {nullptr};
    size_1 = new int;
    *size_1 = L1.string_representation.size();

    int *size_2 {nullptr};
    size_2 = new int;
    *size_2 = L2.string_representation.size();

    std::string *intermediate_numerator {nullptr};
    intermediate_numerator = new std::string;

    std::string *intermediate_remainder {nullptr};
    intermediate_remainder = new std::string;

    std::string *intermediate_quotient {nullptr};
    intermediate_quotient = new std::string;

    std::string *quotient_string {nullptr};
    quotient_string = new std::string;
    *quotient_string = "";

    std::string *remainder {nullptr};
    remainder = new std::string;

    // Go through the edge cases:
    if (L1 < L2) {
        *quotient_string = "0";
        *remainder = L1.string_representation;
        result.push_back(LargeInteger(*quotient_string));
        result.push_back(LargeInteger(*remainder));
        return result;
    } else if (L1 == L2) {
        *quotient_string = "1";
        *remainder = "0";
        result.push_back(LargeInteger(*quotient_string));
        result.push_back(LargeInteger(*remainder));
        return result;
    } else if (*size_1 - *size_2 <= 1) {
        return quotient(L1, L2);
    }

    // Can now assume that L1 and L2 differe by at least two digits:

    // First, determine the number of digits of quotient_string, and do the first division

    int *length_of_quotient {nullptr};
    length_of_quotient = new int;

    if (L2 <= L1.string_representation.substr(0, *size_2)) {
        *length_of_quotient = (*size_1 - *size_2 + 1);
        *quotient_string += quotient(L1.string_representation.substr(0, *size_2), L2)[0].string_representation;
        *intermediate_remainder = quotient(L1.string_representation.substr(0, *size_2), L2)[1].string_representation;
        if (*intermediate_remainder == "0") {
            *intermediate_remainder = "";
        }
        *intermediate_numerator = *intermediate_remainder + L1.string_representation[*size_2];
    } else {
        *length_of_quotient = (*size_1 - *size_2);
        *quotient_string += quotient(L1.string_representation.substr(0, *size_2 + 1), L2)[0].string_representation;
        *intermediate_remainder = quotient(L1.string_representation.substr(0, *size_2 + 1), L2)[1].string_representation;
        if (*intermediate_remainder == "0") {
            *intermediate_remainder = "";
        }
        *intermediate_numerator = *intermediate_remainder + L1.string_representation[*size_2 + 1];
    }

    // Now iterate through the rest of the division:

    int *offset {nullptr};
    offset = new int;
    if (*length_of_quotient == *size_1 - *size_2) {
        *offset = 1;
    } else {
        *offset = 0;
    }

    for (int i = 1; i < *length_of_quotient; i++) {
        if (i == *length_of_quotient - 1) {
            if (L2 > LargeInteger(*intermediate_numerator)) {
                *quotient_string += "0";
                *remainder = *intermediate_remainder + L1.string_representation[*size_1 - 1];
                break;
            }
            *quotient_string += quotient(LargeInteger(*intermediate_numerator), L2)[0].string_representation;
            *remainder = quotient(LargeInteger(*intermediate_numerator), L2)[1].string_representation;
            break;
        }
        if (L2 > LargeInteger(*intermediate_numerator)) {
            *quotient_string += "0";
            *intermediate_remainder = *intermediate_numerator;
            if (*intermediate_remainder == "0") {
                *intermediate_remainder = "";
            }
            *intermediate_numerator = *intermediate_remainder + L1.string_representation[*size_2 + i + *offset];
            continue;
        } else {
            *quotient_string += quotient(LargeInteger(*intermediate_numerator), L2)[0].string_representation;
            *intermediate_remainder = quotient(LargeInteger(*intermediate_numerator), L2)[1].string_representation;
            if (*intermediate_remainder == "0") {
                *intermediate_remainder = "";
            }
            *intermediate_numerator = *intermediate_remainder + L1.string_representation[*size_2 + i + *offset];
        }
    }

    result.push_back(LargeInteger(*quotient_string));
    result.push_back(LargeInteger(*remainder));

    delete size_1;
    delete size_2;
    delete intermediate_numerator;
    delete intermediate_remainder;
    delete intermediate_quotient;
    delete quotient_string;
    delete length_of_quotient;
    delete offset;

    return result;
}

LargeInteger LargeInteger::gcd(LargeInteger L1, LargeInteger L2) {
    // Implements the Euclidean algorithm to compute gcd(a, b)

    LargeInteger result;
    
    LargeInteger *a {nullptr};
    a = new LargeInteger;

    LargeInteger *b {nullptr};
    b = new LargeInteger;

    LargeInteger *numerator {nullptr};
    numerator = new LargeInteger;

    LargeInteger *denominator {nullptr};
    denominator = new LargeInteger;
    
    std::vector<LargeInteger> *remainders {nullptr};
    remainders = new std::vector<LargeInteger>;

    // Deal with edge cases, and set a and b:

    if ((L1 == LargeInteger("0")) && (L2 != LargeInteger ("0"))) {
        return L2;
    } else if ((L1 != LargeInteger("0")) && (L2 == LargeInteger ("0"))) {
        return L1;
    } else if ((L1 != LargeInteger("0")) && (L2 == LargeInteger ("0"))) {
        return L1;
    } else if (L1 < L2) {
        *a = L2;
        *b = L1;
    } else if (L1 == L2) {
        return L1;
    } else {
        *a = L1;
        *b = L2;
    }

    if (long_division(*a, *b)[1] == LargeInteger("0")) {
        result = *b;
        return result;
    }

    *numerator = *a;
    *denominator = *b;

    (*remainders).push_back(long_division(*a, *b)[1]);

    while ((*remainders).back() != LargeInteger("0")) {
        *numerator = *denominator;
        *denominator = (*remainders).back();
        (*remainders).push_back(long_division(*numerator, *denominator)[1]);
    }

    result = (*remainders)[(*remainders).size() - 2];

    delete a;
    delete b;
    delete remainders;

    return result;
}

std::vector<LargeInteger> LargeInteger::extended_euclidean(LargeInteger a, LargeInteger b) {
    // Implements the extended Euclidean algorithm: returns the vector (gcd(a, b), u, v),
    // where u and v are integers satisficying au + bv = gcd(a, b), and u is as small as possible
    // (see Exercise 1.12 in Hoffstein, Pipher, Silverman)

    std::vector<LargeInteger> result {}; 

    if (a == LargeInteger("0") || b == LargeInteger("0")) {
        for (int i = 0; i < 3; i++) {
            result.push_back(LargeInteger("0"));
        }
        return result;
    }

    LargeInteger *u {nullptr};
    u = new LargeInteger;

    LargeInteger *v {nullptr};
    v = new LargeInteger;

    LargeInteger *g {nullptr};
    g = new LargeInteger;

    LargeInteger *x {nullptr};
    x = new LargeInteger;

    LargeInteger *y {nullptr};
    y = new LargeInteger;

    LargeInteger *s {nullptr};
    s = new LargeInteger;

    LargeInteger *q {nullptr};
    q = new LargeInteger;

    LargeInteger *t {nullptr};
    t = new LargeInteger;

    *u = LargeInteger("1");
    *g = a;
    *x = LargeInteger("0");
    *y = b;

    while (*y != LargeInteger("0")) {
        *q = long_division(*g, *y)[0];
        *t = long_division(*g, *y)[1];
        *s = *u - (*q)*(*x);
        *u = *x;
        *g = *y;
        *x = *s;
        *y = *t;
    }

    *v = (*g - (a)*(*u)) / (b);

    while ((*u).is_neg()) {
        *u = (*u) + (b / (*g));
        *v = *v - (a / (*g));
    }

    result.push_back(*g);
    result.push_back(*u);
    result.push_back(*v);


    delete u;
    delete v;
    delete g;
    delete x;
    delete y;
    delete s;
    delete q;
    delete t;

    return result;
}

// Overloaded Unary Operators

LargeInteger LargeInteger::operator-() const {
    if (string_representation[0] == '-') {
        return LargeInteger(string_representation.substr(1));
    } else {
        return LargeInteger("-" + string_representation);
    }
}

// Overloaded Binary Operators

LargeInteger LargeInteger::operator+(const LargeInteger &rhs) const {
    LargeInteger L1 = LargeInteger(string_representation);
    LargeInteger L2 = LargeInteger(rhs.string_representation);

    if (L1.is_neg() && L2.is_non_neg()) {
        return L2 - (-L1);
    } else if (L1.is_non_neg() && L2.is_neg()) {
        return L1 - (-L2);
    } else if (L1.is_neg() && L2.is_neg()) {
        return -((-L1) + (-L2));
    }


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
    *carrier = 0;
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

   if ((*size_1) <= 14 && (*size_2 <= 3)) {
    long long int *sumPtr {nullptr};
    sumPtr = new long long int;

    *sumPtr = to_base_ten(*summand_1) + to_base_ten(*summand_2);
    LargeInteger L = LargeInteger(std::to_string(*sumPtr));
    delete size_1;
    delete size_2;
    delete summand_1;
    delete summand_2;
    delete carrier;
    delete sumPtr;
    return L;
   }

   // Assume size_1 >= 15, size_2 >= 4:

   *summand_2 = string_of_zeroes(*size_1 - *size_2) + *summand_2;

   

    for (int i = 0; i < *size_1; i++) {
        std::string *sumPtr {nullptr};
        sumPtr = new std::string;
        *sumPtr = std::to_string(from_char_to_int((*summand_1)[*size_1 - 1 - i]) + from_char_to_int((*summand_2)[*size_1 - 1 - i]) + *carrier);
        if (i == *size_1 - 1) {
            std::reverse((*sumPtr).begin(), (*sumPtr).end());
            result += *sumPtr;
            break;
        }
        if ((*sumPtr).size() == 2) {
            result += (*sumPtr)[1];
            *carrier = 1;
        } else {
            result += *sumPtr;
            *carrier = 0;
        }
    }

    delete size_1;
    delete size_2;
    delete summand_1;
    delete summand_2;
    delete carrier;

    std::reverse(result.begin(), result.end());

    return LargeInteger(result);
}

LargeInteger LargeInteger::operator-(const LargeInteger &rhs) const {
    LargeInteger L1 = LargeInteger(string_representation);
    LargeInteger L2 = LargeInteger(rhs.string_representation);

    if (L1.is_neg() && L2.is_non_neg()) {
        return -(-L1 + L2);
    }
    else if (L1.is_non_neg() && L2.is_neg()) {
        return (L1 + (-L2));
    } else if (L1.is_neg() && L2.is_neg()) {
        return -L2 - -(L1);
    }

    if (L1 < L2) {
        return -(L2 - L1);
    } else if (L1 == L2) {
        return LargeInteger("0");
    } else { // can assume now that L1 > L2, resulting in a positive subtraction
        int *size_1 {nullptr}; // size of the integer with more digits
        size_1 = new int;
        int *size_2 {nullptr}; // size of the integers with less digits
        size_2 = new int;
        std::string *summand_1 {nullptr}; // the string with more digits
        summand_1 = new std::string;
        std::string *summand_2 {nullptr}; // the string with less digits
        summand_2 = new std::string;
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
            long long int *diffPtr {nullptr};
            diffPtr = new long long int;

            *diffPtr = to_base_ten(*summand_1) - to_base_ten(*summand_2);
            LargeInteger L = LargeInteger(std::to_string(*diffPtr));
            delete size_1;
            delete size_2;
            delete summand_1;
            delete summand_2;
            return L;
        }

        // Assume size_1 >= 15, size_2 >= 4

        *summand_2 = string_of_zeroes(*size_1 - *size_2) + rhs.string_representation;

        for (int i = 0; i < *size_1; i++) {
            int diffPtr = from_char_to_int((*summand_1)[*size_1 - 1 - i]) - from_char_to_int((*summand_2)[*size_1 - 1 - i]);
            if (diffPtr >= 0) {
                result += std::to_string(diffPtr);
            } else {
                diffPtr = from_char_to_int((*summand_1)[*size_1 - 1 - i]) + 10 - from_char_to_int((*summand_2)[*size_1 - 1 - i]);
                result += std::to_string(diffPtr);

                int ctr = 1;
                while ((*summand_1)[*size_1 - 1 - (i + ctr)] == '0') {
                    (*summand_1)[*size_1 - 1 - (i + ctr)] = '9';
                    ctr += 1;
                }
                (*summand_1)[*size_1 - 1 - (i + ctr)] = std::to_string((int)((*summand_1)[*size_1 - 1 - (i + ctr)]) - 48 - 1)[0];
            }
        }

        delete size_1;
        delete size_2;
        delete summand_1;
        delete summand_2;

        std::reverse(result.begin(), result.end());

        return LargeInteger(no_leading_zeroes(result));

    }
}

LargeInteger LargeInteger::operator*(const LargeInteger &rhs) const {
    LargeInteger L1 = LargeInteger(string_representation);
    LargeInteger L2 = LargeInteger(rhs.string_representation);

    if (L1.is_neg() && L2.is_non_neg()) {
        return -(-(L1) * L2);
    } else if (L1.is_non_neg() && L2.is_neg()) {
        return -((-L2) * L1);
    } else if (L1.is_neg() && L2.is_neg()) {
        return (-L1) * (-L2);
    }

    int *size_1 {nullptr}; // size of the integer with more digits
    size_1 = new int;
    int *size_2 {nullptr}; // size of the integers with less digits
    size_2 = new int;
    std::string *term_1 {nullptr}; // the string with more digits
    term_1 = new std::string;
    std::string *term_2 {nullptr}; // the string with less digits
    term_2 = new std::string;
    std::vector<std::string> *vecOfSummands {nullptr};
    vecOfSummands = new std::vector<std::string>;
    std::string *prodPtr {nullptr};
    prodPtr = new std::string;
    int *carrier {nullptr};
    carrier = new int;
    *carrier = 0;
    std::string result = "";
    LargeInteger L = LargeInteger("0");

    // Code block below sets size_1, size_2, summand_1, and summand_2 correctly

    if (string_representation.size() >= rhs.string_representation.size()) {
        *size_1 = string_representation.size();
        *size_2 = rhs.string_representation.size();
        *term_1 = string_representation;
        *term_2 = rhs.string_representation;
    } else {
        *size_1 = rhs.string_representation.size();
        *size_2 = string_representation.size();
        *term_1 = rhs.string_representation;
        *term_2 = string_representation;
    }

    // Edge cases: size_1 <= 14, size_2 <= 3:

    if (*size_1 <= 14 && *size_2 <= 3) {
        delete size_1;
        delete size_2;
        delete term_1;
        delete term_2;
        delete vecOfSummands;
        delete prodPtr;
        delete carrier;

        return LargeInteger(std::to_string(to_base_ten(string_representation) * to_base_ten(rhs.string_representation)));
    }

    // Put empty strings in vecOfSummands:

    for (int i = 0; i < *size_2; i++) {
        (*vecOfSummands).push_back("");
    }

    
    for (int i = 0; i < *size_2; i++) {
        for (int j = 0; j < *size_1; j++) {
            *prodPtr = std::to_string((from_char_to_int((*term_2)[*size_2 - 1 - i]) * from_char_to_int((*term_1)[*size_1 - 1 - j])) + *carrier);
            if (j == *size_1 - 1) {
                std::reverse((*prodPtr).begin(), (*prodPtr).end());
                (*vecOfSummands)[i] += *prodPtr;
                *carrier = 0;
                break;
            }
            if ((*prodPtr).size() == 2) {
                (*vecOfSummands)[i] += (*prodPtr)[1];
                *carrier = from_char_to_int((*prodPtr)[0]);
            } else {
                (*vecOfSummands)[i] += (*prodPtr)[0];
                *carrier = 0;
            }
        }
    }
    

   

    for (int i = 0; i < *size_2; i++) {
        std::reverse((*vecOfSummands)[i].begin(), (*vecOfSummands)[i].end());
    }

    for (int i = 0; i < (*vecOfSummands).size(); i++) {
        L = L + LargeInteger((*vecOfSummands)[i] + string_of_zeroes(i));
    }
    

    delete size_1;
    delete size_2;
    delete term_1;
    delete term_2;
    delete prodPtr;
    delete carrier;
    delete vecOfSummands;

    return L;
}

LargeInteger LargeInteger::operator%(const LargeInteger &rhs) const {
    return long_division(LargeInteger(string_representation), LargeInteger(rhs.string_representation))[1];
}

LargeInteger LargeInteger::operator/(const LargeInteger &rhs) const {
    return long_division(LargeInteger(string_representation), LargeInteger(rhs.string_representation))[0];
}
    

bool LargeInteger::operator<(const LargeInteger &rhs) const {
    LargeInteger L1 = LargeInteger(string_representation);
    LargeInteger L2 = LargeInteger(rhs.string_representation);

    if (L1 == L2) {
        return false;
    }

    if (L1.is_neg() && L2.is_non_neg()) {
        return true;
    } else if (L1.is_non_neg() && L2.is_neg()) {
        return false;
    } else if (L1.is_neg() && L2.is_neg()) {
        return (-L1) > (-L2);
    }

    if (string_representation.size() < rhs.string_representation.size()) {
        return true;
    }
    else if (rhs.string_representation.size() < string_representation.size()) {
        return false;
    } else {
        for (int i = 0; i < string_representation.size(); i++) {
            if (from_char_to_int(string_representation[i]) < from_char_to_int(rhs.string_representation[i])) {
                return true;
            } else if (from_char_to_int(string_representation[i]) > from_char_to_int(rhs.string_representation[i])) {
                return false;
            }
        }
    }
    return false;
}

bool LargeInteger::operator==(const LargeInteger &rhs) const {
    LargeInteger L1 = LargeInteger(string_representation);
    LargeInteger L2 = LargeInteger(rhs.string_representation);

    if (L1.is_neg() && L2.is_non_neg()) {
        return false;
    } else if (L1.is_non_neg() && L2.is_neg()) {
        return false;
    } else if (L1.is_neg() && L2.is_neg()) {
        return (-L1) == (-L2);
    }
    
    if (string_representation.size() != rhs.string_representation.size()) {
        return false;
    } else {
        for (int i = 0; i < string_representation.size(); i++) {
            if (from_char_to_int(string_representation[i]) != from_char_to_int(rhs.string_representation[i])) {
                return false;
            }
        }
    }

    return true;

}

bool LargeInteger::operator>(const LargeInteger &rhs) const {

    LargeInteger L1 = LargeInteger(string_representation);

    LargeInteger L2 = LargeInteger(rhs.string_representation);

    bool bool_1 = (L1 < L2);
    bool bool_2 = (L1 == L2);

    if ((!bool_1) && (!bool_2)) {
        return true;
    } else {
        return false;
    }

}

bool LargeInteger::operator<=(const LargeInteger &rhs) const {

    LargeInteger L1 = LargeInteger(string_representation);

    LargeInteger L2 = LargeInteger(rhs.string_representation);

    if ((L1 < L2) || (L1 == L2)) {
        return true;
    } else {
        return false;
    }
}

bool LargeInteger::operator>=(const LargeInteger &rhs) const {
    LargeInteger L1 = LargeInteger(string_representation);

    LargeInteger L2 = LargeInteger(rhs.string_representation);

    if ((L1 > L2) || (L1 == L2)) {
        return true;
    } else {
        return false;
    }
}

bool LargeInteger::operator!=(const LargeInteger &rhs) const {
    LargeInteger L1 = LargeInteger(string_representation);

    LargeInteger L2 = LargeInteger(rhs.string_representation);

    if (L1 == L2) {
        return false;
    } else {
        return true;
    }
}

std::string LargeInteger::to_binary() {
    // Returns the binary bit string of the LargeInteger

    // Deal with edge cases:

    if (string_representation == "0") {
        return "0";
    }

    std::string result = "";

    LargeInteger *quotient {nullptr};
    quotient = new LargeInteger;
    *quotient = LargeInteger(string_representation);

    LargeInteger *remainder {nullptr};
    remainder = new LargeInteger;

    while (*quotient != LargeInteger("0")) {
       *remainder = long_division(*quotient, LargeInteger("2"))[1];
       *quotient = long_division(*quotient, LargeInteger("2"))[0];
       result += (*remainder).string_representation;
    }

    delete quotient;
    delete remainder;

    return result;
}

LargeInteger LargeInteger::exponentiate(LargeInteger exponent, LargeInteger modulus) {
    // Returns g^(exponent) mod modulus

    LargeInteger result = LargeInteger("1");

    std::string *bitstring {nullptr};
    bitstring = new std::string;
    *bitstring = exponent.to_binary();

    LargeInteger *previous_power {nullptr};
    previous_power = new LargeInteger;
    *previous_power = LargeInteger("1");
    
    LargeInteger *current_power {nullptr};
    current_power = new LargeInteger;
    *current_power = LargeInteger(string_representation);


    for (int i = 0; i < (*bitstring).size(); i++) {
        *current_power = ((*current_power) * (*previous_power)) % modulus;
        *previous_power = *current_power % modulus;
        if ((*bitstring)[i] == '1') {
            result = (result * *current_power) % modulus;
        } else {
            continue;
        }
    }

    delete bitstring;
    delete previous_power;
    delete current_power;

    return result;
}

bool LargeInteger::fermat_test(int tests) {
    // Uses Fermat's Little Theorem to test for compositeness

    bool result {};

    LargeInteger *fermat_calculation {nullptr};
    fermat_calculation = new LargeInteger;

    if (tests < 1) {
        std::cerr << "Must choose a positive number of tests" << std::endl;
        exit(1);
    }
    std::vector<LargeInteger> *small_primes {nullptr};
    small_primes = new std::vector<LargeInteger>;

    (*small_primes).push_back(LargeInteger("2"));
    (*small_primes).push_back(LargeInteger("3"));
    (*small_primes).push_back(LargeInteger("5"));
    (*small_primes).push_back(LargeInteger("7"));
    (*small_primes).push_back(LargeInteger("11"));

    for (auto l: *small_primes) {
        if (LargeInteger(string_representation) == l) {
            std::cout << "The integer " << string_representation << " is prime." << std::endl;
            result = false;
            return result;
        }
    }

    for (auto l: *small_primes) {
        if (LargeInteger(string_representation) % l == LargeInteger("0")) {
            std::cout << "The integer " << string_representation << " is composite, it is divisible by " << l.string_representation << std::endl;
            return true;
        }
    }

    for (int a = 2; a < 2 + tests; a++) {
        *fermat_calculation = LargeInteger(std::to_string(a)).exponentiate(LargeInteger(string_representation), LargeInteger(string_representation));
        if (*fermat_calculation != LargeInteger(std::to_string(a))) {
            std::cout << "The integer " << string_representation << " is composite because " << a << " is a Fermat witness" << std::endl;
            result = true;
            break;
        }
    }

    result = false;

    std::cout << "I couldn't find a Fermat witness after running " << tests << " tests. The integer " << string_representation << " may be prime." << std::endl;


    delete small_primes;
    delete fermat_calculation;

    return result;
}

bool LargeInteger::miller_rabin_witness(LargeInteger a) {
    // Checks if a is a Miller-Rabin witness to the compositeness of the odd integer LargeInteger = n in question.

    bool result {};

    // Check if a is trivially a witness i.e gcd(n, a) != 1 :
    if ((gcd(LargeInteger(string_representation), a) != LargeInteger("1")) || (LargeInteger(string_representation) % LargeInteger("2") == LargeInteger("0"))) {
        result = true;
        return result;
    }

    // Can now assume that gcd(n, a) = 1 and n is odd.

    // Compute k so that n - 1 = 2^k * q, where q is odd

    LargeInteger *subtr_one {nullptr};
    subtr_one = new LargeInteger;
    *subtr_one = LargeInteger(string_representation) - LargeInteger("1");

    LargeInteger *k {nullptr};
    k = new LargeInteger;
    *k = LargeInteger("0");

    LargeInteger *q {nullptr};
    q = new LargeInteger;
    *q = *subtr_one;

    LargeInteger *second_quantity {nullptr};
    second_quantity = new LargeInteger;

    while (*q % LargeInteger("2") == LargeInteger("0")) {
        *k = *k + LargeInteger("1");
        *q = long_division(*q, LargeInteger("2"))[0];
    }

    // Check the first Miller-Rabin condition:

    if (a.exponentiate(*q, LargeInteger(string_representation)) == LargeInteger("1")) {
        result = false;
    } else {
        result = true;
    }

    // Check the second Miller-Rabin condition:

    *second_quantity = a.exponentiate(*q, LargeInteger(string_representation));

    if (*second_quantity == LargeInteger("1") || *second_quantity == *subtr_one) {
        result = false;
    } 

    for (int i = 1; i < to_base_ten((*k).string_representation); i++) {
        if (result == false) {
            break;
        }
        *second_quantity = ((*second_quantity) * (*second_quantity)) % LargeInteger(string_representation);
        if (*second_quantity == *subtr_one) {
            result = false;
            break;
        }
    }
    
    delete subtr_one;
    delete k;
    delete q;
    delete second_quantity;

    return result;
}

bool LargeInteger::miller_rabin_test_verbose() {
    // Runs the Miller-Rabin test on n; displays witnesses/non-witnesses to the user

    bool result {};

    // Make vector of small primes to deal with small inputs:

    std::vector<LargeInteger> *small_primes {nullptr};
    small_primes = new std::vector<LargeInteger>;

    (*small_primes).push_back(LargeInteger("2"));
    (*small_primes).push_back(LargeInteger("3"));
    (*small_primes).push_back(LargeInteger("5"));
    (*small_primes).push_back(LargeInteger("7"));
    (*small_primes).push_back(LargeInteger("11"));
    (*small_primes).push_back(LargeInteger("13"));
    (*small_primes).push_back(LargeInteger("17"));
    (*small_primes).push_back(LargeInteger("19"));
    (*small_primes).push_back(LargeInteger("23"));
    (*small_primes).push_back(LargeInteger("29"));
    (*small_primes).push_back(LargeInteger("31"));
    (*small_primes).push_back(LargeInteger("37"));
    (*small_primes).push_back(LargeInteger("41"));
    (*small_primes).push_back(LargeInteger("43"));
    (*small_primes).push_back(LargeInteger("47"));
    (*small_primes).push_back(LargeInteger("53"));
    (*small_primes).push_back(LargeInteger("59"));
    (*small_primes).push_back(LargeInteger("61"));
    (*small_primes).push_back(LargeInteger("67"));
    (*small_primes).push_back(LargeInteger("71"));
    (*small_primes).push_back(LargeInteger("73"));
    (*small_primes).push_back(LargeInteger("79"));
    (*small_primes).push_back(LargeInteger("83"));
    (*small_primes).push_back(LargeInteger("89"));
    (*small_primes).push_back(LargeInteger("97"));

    // Trivial Cases:

    for (auto p: *small_primes) {
        if (LargeInteger(string_representation) % p == LargeInteger("0")) {
            result = true;
            std::cout << "The integer " << string_representation << " is composite, it is divisible by " << p.string_representation << std::endl;
            return result;
        }
    }

    // Now assume the input is sufficiently large. 

    // First, generate 50 random rational numbers < 1:

    std::vector<Rational> *potential_witnesses {nullptr};
    potential_witnesses = new std::vector<Rational>;
    *potential_witnesses = random_rationals(50, 100, 100);

    LargeInteger *potential_witness {nullptr};
    potential_witness = new LargeInteger;

    for (int i = 0; i < (*potential_witnesses).size(); i++) {
        *potential_witness = ((*potential_witnesses)[i]).get_numerator() * (LargeInteger(string_representation) / ((*potential_witnesses)[i].get_denominator()));
        if (LargeInteger(string_representation).miller_rabin_witness(*potential_witness) == true) {
            std::cout << "The integer " << string_representation << " is composite, with Miller-Rabin witness " << (*potential_witness).string_representation << std::endl;
            result = true;
            return result;
        }
        (*potential_witnesses)[i] = Rational(*potential_witness, LargeInteger("1"));
        std::cout << (*potential_witness).string_representation << " is not a witness" << std::endl;
    }

    result = false;

    std::cout << "The 50 integers above are not Miller-Rabin witnesses to the compositeness of " << string_representation << std::endl;

    std::cout << "The integer " << string_representation << " is likely prime" << std::endl;


    delete small_primes;
    delete potential_witnesses;

    return result;


}

bool LargeInteger::miller_rabin_test(LargeInteger n) {
    return true;
}

LargeInteger LargeInteger::random_prime(int bitsize) {
    return LargeInteger("1");
}
