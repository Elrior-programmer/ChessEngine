#include "Bitboard.h"
Bitboard::Bitboard() {
    value = 0ULL;
}

Bitboard::Bitboard(unsigned long long val) {
    value = val;
}

Bitboard::~Bitboard() {}

unsigned long long Bitboard::get_value() const {
    return this->value;
}

void Bitboard::set_value(unsigned long long val) {
    this->value = val;
}

unsigned long long Bitboard::get_bit(int square) {
    return (this->value & (1ULL << square));
}

void Bitboard::set_bt1(int square) {
    this->value |= (1ULL << square);
}

void Bitboard::set_bt0(int square) {
    if (this->get_bit(square)) this->value ^= (1ULL << square); 
}

void Bitboard::write() {
    std::cout << "  a b c d e f g h " << std::endl;
    unsigned long long mask = 1ULL;
    for(int i = 0 ; i < 8 ; i++) {
        std::cout<<i+1;
        for(int j = 0 ; j < 8 ; j++) {
            if(this->get_bit(i*8+j)==mask) {
                std::cout<<" "<<1;
            }
            else {
                std::cout<<" "<<0;
            }
            mask = mask << 1;
        }
        std::cout<<" "<<i+1<<std::endl;
    }
    std::cout << "  a b c d e f g h " << std::endl;
}