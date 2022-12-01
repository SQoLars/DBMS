#pragma once

#include <string>

namespace parse {

    std::string ToLower(std::string string) {
        for (int i(0); i < string.length(); i++) {
            if (string[i] >= 'A' && string[i] <= 'Z')
                string[i] += 32;
        }
        return string;
    }

    std::string ToUpper(std::string string) {
        for (int i(0); i < string.length(); i++) {
            if (string[i] >= 'a' && string[i] <= 'z')
                string[i] -= 32;
        }
        return string;
    }
    void ToUpper(std::string* string) {
        for (int i(0); i < (*string).length(); i++) {
            if ((*string)[i] >= 'a' && (*string)[i] <= 'z')
                (*string)[i] -= 32;
        }
    }

    int checkByteOrderMarks(const std::string test) {
        if ((unsigned char)test[0] == 0xEF &&
            (unsigned char)test[1] == 0xBB &&
            (unsigned char)test[2] == 0xBF
            ) {
            return 3;
        } // UTF-8

        if ((
            (unsigned char)test[0] == 0xFE &&
            (unsigned char)test[1] == 0xFF
            )||(
            (unsigned char)test[0] == 0xFF &&
            (unsigned char)test[1] == 0xFE
            )) {
            return 2;
        } // UTF-16

        if ((
            (unsigned char)test[0] == 0x00 &&
            (unsigned char)test[1] == 0x00 &&
            (unsigned char)test[2] == 0xFE &&
            (unsigned char)test[3] == 0xFF
            ) || (
            (unsigned char)test[0] == 0xFF &&
            (unsigned char)test[1] == 0xFE &&
            (unsigned char)test[2] == 0x00 &&
            (unsigned char)test[3] == 0x00
            )) {
            return 4;
        } // UTF-32

        if ((unsigned char)test[0] == 0x2B &&
            (unsigned char)test[1] == 0x2F &&
            (unsigned char)test[2] == 0x76
            ) {
            return 3;
        } // UTF-7

        if ((unsigned char)test[0] == 0xF7 &&
            (unsigned char)test[1] == 0x64 &&
            (unsigned char)test[2] == 0x4c
            ) {
            return 3;
        } // UTF-1

        if ((unsigned char)test[0] == 0xDD &&
            (unsigned char)test[1] == 0x73 &&
            (unsigned char)test[2] == 0x66 &&
            (unsigned char)test[3] == 0x73
            ) {
            return 4;
        } // UTF-EBCDIC

        if ((unsigned char)test[0] == 0x0E &&
            (unsigned char)test[1] == 0xFE &&
            (unsigned char)test[2] == 0xFF
            ) {
            return 3;
        } // SCSU

        if ((unsigned char)test[0] == 0xFB &&
            (unsigned char)test[1] == 0xEE &&
            (unsigned char)test[2] == 0x28
            ) {
            return 3;
        } // BOCU-1

        if ((unsigned char)test[0] == 0x84 &&
            (unsigned char)test[1] == 0x31 &&
            (unsigned char)test[2] == 0x95 &&
            (unsigned char)test[3] == 0x33
            ) {
            return 4;
        } // GB18030
        return 0;
    }

    void RemoveByteOrderMarks(std::string* test) {
        (*test).erase(0, checkByteOrderMarks(*test));
    }

}