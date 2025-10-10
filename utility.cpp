#include "utility.h"

std::string toBinary(uint64_t number) {
    const int BITS = 64;
    std::string result;

    unsigned long long mask = 1ULL << (BITS - 1); // maska od MSB

    for (int i = 0; i < BITS; i++) {
        result += (number & mask) ? '1' : '0';
        mask >>= 1;
    }

    return result;
}