#ifndef _CAESAR_H_
#define _CAESAR_H_

#include <string>
#include <vector>

class Caesar {
    private:
        std::string plaintext_string;
        std::vector<char> punctuation_characters;
        std::vector<char> integer_characters;
        std::vector<char> upper_case_characters;
        std::vector<char> lower_case_characters;
    
    public:
        Caesar(std::string s) {
            plaintext_string = s;

            /* On ASCII table,
                    punctuation locations are: 32-47, 58-64, 91-96, 123-126
                    integer locations are: 48-57
                    upper case letter locations are: 65-90
                    lower case letter locations are: 97-122
            */

            // Populate punctuation_characters
            
            std::vector<int> punctuation_locations;

            for (int i = 32; i < 127; i++){
                if ((i >= 32 && i <= 47) || (i >= 58 && i <= 64) || (i >= 91 && i <= 96) || (i >= 123 && i <= 126)){
                    punctuation_locations.push_back(i);
                }
            }
            
            for (auto i: punctuation_locations) {
                punctuation_characters.push_back(char(i));
            }

            // Populate integers_characters

            for (int i = 48; i < 58; i++) {
                integer_characters.push_back(char(i));
            }

            // Populate upper_case_characters

            for (int i = 65; i < 91; i++) {
                upper_case_characters.push_back(char(i));
            }

            // Populate lower_case_characters

            for (int i = 97; i < 123; i++) {
                lower_case_characters.push_back(char(i));
            }

            
        }

        // Getters
        std::string get_plaintext_string();
        std::vector<char> get_punctuation_characters();
        std::vector<char> get_integer_characters();
        std::vector<char> get_upper_case_characters();
        std::vector<char> get_lower_case_characters();

        // Setters
        void set_plaintext_string(std::string s);

        // Encryption method

        std::string encrypt();
};


#endif