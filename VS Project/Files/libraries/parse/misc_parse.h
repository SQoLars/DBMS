#pragma once

#include <string>

namespace parse {

    std::string StringToLower(std::string string) {
        for (int i(0); i < string.length(); i++) {
            if (string[i] >= 'A' && string[i] <= 'Z')
                string[i] += 32;
        }
        return string;
    }

    std::string StringToUpper(std::string string) {
        for (int i(0); i < string.length(); i++) {
            if (string[i] >= 'a' && string[i] <= 'z')
                string[i] -= 32;
        }
        return string;
    }

}