#ifndef _RATIONAL_H_
#define _RATIONAL_H_

#include "largeinteger.h"
#include <string>

class Rational {
    private:
        LargeInteger numerator;
        LargeInteger denominator;
        std::string string_representation;
    public:
        Rational() {
            numerator = LargeInteger("1");
            denominator = LargeInteger("1");
            string_representation = numerator.get_string_representation() + "/" + denominator.get_string_representation();
        }

        Rational(LargeInteger num, LargeInteger den) {
            numerator = num;
            denominator = den;
            string_representation = numerator.get_string_representation() + "/" + denominator.get_string_representation();
        }

        // Getters
        LargeInteger get_numerator();
        LargeInteger get_denominator();
        std::string get_string_representation();

        // Setters
        void set_numerator(std::string num);
        void set_denominator(std::string den);

        // Simplify
        Rational simplify();

        // Overloaded Binary Operators
        Rational operator+(const Rational &rhs) const;
        Rational operator*(const Rational &rhs) const;
};

#endif 