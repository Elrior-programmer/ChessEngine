#pragma once
#include <iostream>
#include <string>
#include <cstdint>
#include "utility.h"

#define get_bit(bitboard, square) (bitboard & (1ULL << square))
#define set_bt1(bitboard, square) (bitboard |= (1ULL << square))
#define set_bt0(bitboard, square) ( get_bit(bitboard, square) ? bitboard ^= (1ULL << square) : 0)

#define a8 0
#define b8 1
#define c8 2
#define d8 3
#define e8 4
#define f8 5
#define g8 6
#define h8 7

#define a7 8
#define b7 9
#define c7 10
#define d7 11
#define e7 12
#define f7 13
#define g7 14
#define h7 15

#define a6 16
#define b6 17
#define c6 18
#define d6 19
#define e6 20
#define f6 21
#define g6 22
#define h6 23

#define a5 24
#define b5 25
#define c5 26
#define d5 27
#define e5 28
#define f5 29
#define g5 30
#define h5 31

#define a4 32
#define b4 33
#define c4 34
#define d4 35
#define e4 36
#define f4 37
#define g4 38
#define h4 39

#define a3 40
#define b3 41
#define c3 42
#define d3 43
#define e3 44
#define f3 45
#define g3 46
#define h3 47

#define a2 48
#define b2 49
#define c2 50
#define d2 51
#define e2 52
#define f2 53
#define g2 54
#define h2 55

#define a1 56
#define b1 57
#define c1 58
#define d1 59
#define e1 60
#define f1 61
#define g1 62
#define h1 63


const uint64_t not_a_file = 18374403900871474942ULL;
/*
  a b c d e f g h
8 0 1 1 1 1 1 1 1 8
7 0 1 1 1 1 1 1 1 7
6 0 1 1 1 1 1 1 1 6
5 0 1 1 1 1 1 1 1 5
4 0 1 1 1 1 1 1 1 4
3 0 1 1 1 1 1 1 1 3
2 0 1 1 1 1 1 1 1 2
1 0 1 1 1 1 1 1 1 1
  a b c d e f g h
  */
const uint64_t not_h_file = 9187201950435737471ULL;
/*
  a b c d e f g h
8 1 1 1 1 1 1 1 0 8
7 1 1 1 1 1 1 1 0 7
6 1 1 1 1 1 1 1 0 6
5 1 1 1 1 1 1 1 0 5
4 1 1 1 1 1 1 1 0 4
3 1 1 1 1 1 1 1 0 3
2 1 1 1 1 1 1 1 0 2
1 1 1 1 1 1 1 1 0 1
  a b c d e f g h
  */
const uint64_t not_ab_file = 18229723555195321596ULL;
/*
  a b c d e f g h
8 0 0 1 1 1 1 1 1 8
7 0 0 1 1 1 1 1 1 7
6 0 0 1 1 1 1 1 1 6
5 0 0 1 1 1 1 1 1 5
4 0 0 1 1 1 1 1 1 4
3 0 0 1 1 1 1 1 1 3
2 0 0 1 1 1 1 1 1 2
1 0 0 1 1 1 1 1 1 1
  a b c d e f g h
*/
const uint64_t not_gh_file = 4557430888798830399ULL;
/*
  a b c d e f g h
8 1 1 1 1 1 1 0 0 8
7 1 1 1 1 1 1 0 0 7
6 1 1 1 1 1 1 0 0 6
5 1 1 1 1 1 1 0 0 5
4 1 1 1 1 1 1 0 0 4
3 1 1 1 1 1 1 0 0 3
2 1 1 1 1 1 1 0 0 2
1 1 1 1 1 1 1 0 0 1
  a b c d e f g h
  */
void write_bitboard(uint64_t bitboard);

void write_board(uint64_t* w_k, uint64_t* w_q, uint64_t* w_p, uint64_t* w_r, uint64_t* w_b, uint64_t* w_n,
	uint64_t* b_k, uint64_t* b_q, uint64_t* b_p, uint64_t* b_r, uint64_t* b_b, uint64_t* b_n);

void chess_game(std::string FEN);