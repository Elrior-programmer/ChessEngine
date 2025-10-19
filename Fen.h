#pragma once
#include <iostream>
#include <string>
#include <cstdint>
#include <sstream>
#include <vector>

void read_FEN(std::string fen, uint64_t* w_k, uint64_t* w_q, uint64_t* w_p, uint64_t* w_r, uint64_t* w_b, uint64_t* w_n,
	uint64_t* b_k, uint64_t* b_q, uint64_t* b_p, uint64_t* b_r, uint64_t* b_b, uint64_t* b_n,
	bool *turn, bool *w_s_c, bool *w_l_c, bool *b_s_c, bool *b_l_c,
	uint16_t *e_n, int *h_m, int *f_m);

