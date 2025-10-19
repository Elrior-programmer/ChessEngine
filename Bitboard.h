#pragma once
#include <iostream>
class Bitboard
{
private:
    unsigned long long value;
public:
    Bitboard();
    Bitboard(unsigned long long val);
    ~Bitboard();
    unsigned long long get_value() const;
    unsigned long long get_bit(int square);
    void set_bt1(int square);
    void write();
};

