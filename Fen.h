#pragma once
#include <iostream>
#include "Bitboard.h"
#include <string>
#include <sstream>
#include <vector>

void read_FEN(std::string fen, Bitboard* w_k, Bitboard* w_q, Bitboard* w_p, Bitboard* w_r, Bitboard* w_b, Bitboard* w_n,
	Bitboard* b_k, Bitboard* b_q, Bitboard* b_p, Bitboard* b_r, Bitboard* b_b, Bitboard* b_n,
	bool *turn, bool *w_s_c, bool *w_l_c, bool *b_s_c, bool *b_l_c,
	Bitboard *e_n, int *h_m, int *f_m);

