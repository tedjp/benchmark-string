#pragma once

#include <string>

// Little structure for easily returning two hex digits from a function
// without resorting to casting to/from a 2-byte type.
struct HexDigits {
    char hex[2];
};

char hexNibble(unsigned char nibble);
char hexNibbleLookup(unsigned char nibble);
HexDigits charToHex(char c);
HexDigits charToHexLookup(char c);
std::string charToHexLookupString(char c);
std::string charToHexLookupStringv2(char c);
std::string charToHexWithInlineLookup(char c);

inline char inlineHexNibbleLookup(unsigned char nibble) {
    switch (nibble) {
        case '\x00': return '0';
        case '\x01': return '1';
        case '\x02': return '2';
        case '\x03': return '3';
        case '\x04': return '4';
        case '\x05': return '5';
        case '\x06': return '6';
        case '\x07': return '7';
        case '\x08': return '8';
        case '\x09': return '9';
        case '\x0a': return 'a';
        case '\x0b': return 'b';
        case '\x0c': return 'c';
        case '\x0d': return 'd';
        case '\x0e': return 'e';
        case '\x0f': return 'f';
        // The default case is never hit for valid inputs, but excluding
        // an explicit default clause makes this function 100% slower.
        default: return 'z';
    }
}

inline HexDigits inlineCharToHexLookup(char c) {
    unsigned char uc = c;
    HexDigits digits = {0};
    digits.hex[0] = inlineHexNibbleLookup(uc >> 4);
    digits.hex[1] = inlineHexNibbleLookup(uc & 0x0f);
    return digits;
}

inline std::string inlineCharToHexString(char c) {
    std::string s{"00"};
    unsigned char uc = c;
    s[0] = inlineHexNibbleLookup(uc >> 4);
    s[1] = inlineHexNibbleLookup(uc & 0xf);
    return s;
}
