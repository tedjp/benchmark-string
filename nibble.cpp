#include "nibble.h"

// Return the hex encoding of a nibble (low 4 bits)
char hexNibble(unsigned char nibble) {
    if (nibble < '\x0a')
        return '0' + nibble;

    return 'a' + (nibble - 10);
}

char hexNibbleLookup(unsigned char nibble) {
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
        default: return 'z'; // This makes it twice as fast
    }
}

HexDigits charToHex(char c) {
    unsigned char uc = c;
    HexDigits digits = {0};
    digits.hex[0] = hexNibble(uc >> 4);
    digits.hex[1] = hexNibble(uc & 0x0f);
    return digits;
}

HexDigits charToHexLookup(char c) {
    unsigned char uc = c;
    HexDigits digits = {0};
    digits.hex[0] = hexNibbleLookup(uc >> 4);
    digits.hex[1] = hexNibbleLookup(uc & 0x0f);
    return digits;
}

std::string charToHexLookupString(char c) {
    HexDigits digits = charToHexLookup(c);
    return std::string(digits.hex, 2);
}

std::string charToHexLookupStringv2(char c) {
    std::string s{"00"};
    HexDigits digits = charToHexLookup(c);
    s[0] = digits.hex[0];
    s[1] = digits.hex[1];
    return s;
}

std::string charToHexWithInlineLookup(char c) {
    std::string s{"00"};
    s[0] = inlineHexNibbleLookup(c >> 4);
    s[1] = inlineHexNibbleLookup(c & 0xf);
    return s;
}
