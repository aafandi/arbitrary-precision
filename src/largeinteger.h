#ifndef _LARGEINTEGER_H_
#define _LARGEINTEGER_H_

#include <string>
#include <vector>

class LargeInteger {
    private:
        std::string string_representation;
    public:
        // Constructor 
        LargeInteger(std::string s) {
            string_representation = s;
        }

        LargeInteger() {
            string_representation = "0";
        }
        // Getter
        std::string get_string_representation();
        // Setter
        void set_string_representation(std::string s);

        // Methods to Determine Sign

        bool is_neg();
        bool is_non_neg();

        // Static Methods 

        static long long int to_base_ten(std::string s);
        static int from_char_to_int(char c);
        static std::string string_of_zeroes(int n);
        static std::string no_leading_zeroes(std::string s);
        static std::vector<LargeInteger> quotient(LargeInteger L1, LargeInteger L2);
        static std::vector<LargeInteger> long_division(LargeInteger L1, LargeInteger L2);
        static LargeInteger gcd(LargeInteger L1, LargeInteger L2);
        static std::vector<LargeInteger> extended_euclidean(LargeInteger L1, LargeInteger L2);

        // Overloaded Unary Operators

        LargeInteger operator-()const;

        
        // Overloaded Binary Operators
        LargeInteger operator+(const LargeInteger &rhs) const;
        LargeInteger operator-(const LargeInteger &rhs) const;
        LargeInteger operator*(const LargeInteger &rhs) const;
        LargeInteger operator%(const LargeInteger &rhs) const;
        LargeInteger operator/(const LargeInteger &rhs) const;
        bool operator<(const LargeInteger &rhs) const;
        bool operator==(const LargeInteger &rhs) const;
        bool operator>(const LargeInteger &rhs) const;
        bool operator<=(const LargeInteger &rhs) const;
        bool operator>=(const LargeInteger &rhs) const;
        bool operator!=(const LargeInteger &rhs) const;

        // Fast powering algorithm, mod N
        std::string to_binary();
        LargeInteger exponentiate(LargeInteger exponent, LargeInteger modulus);

        // Primality Tests
        bool fermat_test(int tests);
        bool miller_rabin(LargeInteger n);
};

std::vector<int> random_slice(int depth);

#endif