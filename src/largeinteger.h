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
        void set_string_representation(std::string s);
};

#endif