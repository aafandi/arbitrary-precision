#include "largeinteger.h"
#include <string>

// Getter
std::string LargeInteger::get_string_representation() {
    return string_representation;
}
// Setter
void LargeInteger::set_string_representation(std::string s) {
    string_representation = s;
}