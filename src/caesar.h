#ifndef _ELLIPTICCURVE_H_
#define _ELLIPTICCURVE_H_

#include <string>

class caesar {
    private:
        std::string encryptedString;
    
    public:
        caesar(std::string s) {
            encryptedString = s;
        }

        // Getter
        std::string getEncryptedString();

        // Setter
        void setEncryptedString(std::string s);
};

#endif