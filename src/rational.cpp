#include "rational.h"

// Getters

LargeInteger Rational::get_numerator() {
    return numerator;
}

LargeInteger Rational::get_denominator() {
    return denominator;
}

std::string Rational::get_string_representation() {
    return string_representation;
}

// Setters

void Rational::set_numerator(std::string num) {
    numerator = num;
}

// Simplify

Rational Rational::simplify() {
    // Simplifies a Rational into its lowest tersm

    Rational result {};

    LargeInteger *new_numerator {nullptr};
    new_numerator = new LargeInteger;
    *new_numerator = numerator;
    
    LargeInteger *new_denominator {nullptr};
    new_denominator = new LargeInteger;
    *new_denominator = denominator;

    LargeInteger *common_factor {nullptr};
    common_factor = new LargeInteger;

    while (LargeInteger::gcd(*new_numerator, *new_denominator) != LargeInteger("1")) {
        *common_factor = LargeInteger::gcd(*new_numerator, *new_denominator);
        *new_numerator = *new_numerator / *common_factor;
        *new_denominator= *new_denominator / *common_factor;
    }

    result = Rational(*new_numerator, *new_denominator);

    delete new_numerator;
    delete new_denominator;
    delete common_factor;

    return result;
}

void Rational::set_denominator(std::string den) {
    denominator = den;
}

// Overloaded Binary Operators

Rational Rational::operator+(const Rational &rhs) const {

    Rational result {};

    LargeInteger *a {nullptr};
    a = new LargeInteger;
    *a = numerator;

    LargeInteger *b {nullptr};
    b = new LargeInteger;
    *b = denominator;

    LargeInteger *c {nullptr};
    c = new LargeInteger;
    *c = rhs.numerator;

    LargeInteger *d {nullptr};
    d = new LargeInteger;
    *d = rhs.denominator;

    LargeInteger *new_numerator {nullptr};
    new_numerator = new LargeInteger;
    *new_numerator = ((*a) * (*d)) + ((*c) * (*b)); 

    LargeInteger *new_denominator {nullptr};
    new_denominator = new LargeInteger;
    *new_denominator = (*b) * (*d);

    result = Rational(*new_numerator, *new_denominator);

    delete a;
    delete b;
    delete c;
    delete d;
    delete new_numerator;
    delete new_denominator;

    return result;
}

Rational Rational::operator*(const Rational &rhs) const {

    return Rational(numerator * rhs.numerator, denominator * rhs.denominator);

}

bool Rational::operator==(const Rational &rhs) const {
    // Determines of two rational numbers are the same.

    if ((numerator == rhs.numerator) && (denominator == rhs.denominator)) {
        return true;
    } else {
        return false;
    }
}


