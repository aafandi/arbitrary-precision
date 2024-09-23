#ifndef _LARGEINTEGER_H_
#define _LARGEINTEGER_H_

#include <string>

class LargeInteger {
    private:
        std::string string_representation;
    public:
        // Constructor 
        LargeInteger(std::string s) {
            string_representation = s;
        }
        // Getter
        std::string get_string_representation();
        // Setter

        // Static Methods 

        static long long int to_base_ten(std::string s);
        static int from_char_to_int(char c);
        static std::string string_of_zeroes(int n);

        void set_string_representation(std::string s);
        // Overloaded Binary Operators
        LargeInteger operator+(const LargeInteger &rhs) const;
};

#endif