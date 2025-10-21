#include "Fen.h"

/* We start reading fen from black side*/

void read_FEN(std::string fen, Bitboard* w_k, Bitboard* w_q, Bitboard* w_p, Bitboard* w_r, Bitboard* w_b, Bitboard* w_n,
	Bitboard* b_k, Bitboard* b_q, Bitboard* b_p, Bitboard* b_r, Bitboard* b_b, Bitboard* b_n,
	bool *turn, bool *w_s_c, bool *w_l_c, bool *b_s_c, bool *b_l_c,
	Bitboard *e_n, int *h_m, int *f_m)
{
	std::vector<std::string> fenSplit;

	std::stringstream ss(fen);
	std::string token;

	while (ss >> token) {  // domy�lnie tnie po spacji
		fenSplit.push_back(token);
	}

	unsigned long long mask = 1ULL;
	for (short i = 0; i < fenSplit[0].size(); i++) {
		char temp = fen[i];
		switch (temp) {
			//Kings
		case 'k':
			b_k->set_value(b_k->get_value() + mask);
			mask = mask << 1;
			break;
		case 'K':
			w_k->set_value(w_k->get_value() + mask);
			mask = mask << 1;
			break;
			// Queens
		case 'q':
			b_q->set_value(b_q->get_value()+mask);
			mask = mask << 1;
			break;
		case 'Q':
			w_q->set_value(w_q->get_value()+mask);
			mask = mask << 1;
			break;
			// Rooks
		case 'r':
			b_r->set_value(b_r->get_value()+mask);
			mask = mask << 1;
			break;
		case 'R':
			w_r->set_value(w_r->get_value()+mask);
			mask = mask << 1;
			break;
			//Bishops
		case 'b':
			b_b->set_value(b_b->get_value()+mask);
			mask = mask << 1;
			break;
		case 'B':
			w_b->set_value(w_b->get_value()+mask);
			mask = mask << 1;
			break;
			// Knights
		case 'n':
			b_n->set_value(b_n->get_value()+mask);
			mask = mask << 1;
			break;
		case 'N':
			w_n->set_value(w_n->get_value()+mask);
			mask = mask << 1;
			break;
			// Pawns
		case 'p':
			b_p->set_value(b_p->get_value()+mask);
			mask = mask << 1;
			break;
		case 'P':
			w_p->set_value(w_p->get_value()+mask);
			mask = mask << 1;
			break;
			// Numbers
		case '1':
			mask = mask << 1;
			break;
		case '2':
			mask = mask << 2;
			break;
		case '3':
			mask = mask << 3;
			break;
		case '4':
			mask = mask << 4;
			break;
		case '5':
			mask = mask << 5;
			break;
		case '6':
			mask = mask << 6;
			break;
		case '7':
			mask = mask << 7;
			break;
		case '8':
			mask = mask << 8;
			break;
		}
	}
	(fenSplit[1] == "w") ? *turn = true : *turn = false;
	if (fenSplit[2] == "-") {
		*w_s_c = *w_l_c = *b_s_c = *b_l_c = false;
	}
	else if (fenSplit[2].size() == 4) {
		*w_s_c = *w_l_c = *b_s_c = *b_l_c = true;
	}
	if (fenSplit[2].find("K") != std::string::npos) {
		*w_s_c = true;
	}
	else {
		*w_s_c = false;
	}
	if (fenSplit[2].find("Q") != std::string::npos) {
		*w_l_c = true;
	}
	else {
		*w_l_c = false;
	}
	if (fenSplit[2].find("k") != std::string::npos) {
		*b_s_c = true;
	}
	else {
		*b_s_c = false;
	}
	if (fenSplit[2].find("q") != std::string::npos) {
		*b_l_c = true;
	}
	else {
		*b_l_c = false;
	}
	unsigned long long mask2 = 1;
	if (fenSplit[3] == "-") {
		mask2 = 0;
	}
	if (fenSplit[3][1] == '6') {
		mask2 = mask2 << 8;
	}
	mask2 = mask2 << fenSplit[3][0] - 'a';

	e_n->set_value(mask2);
	*h_m = stoi(fenSplit[4]);
	*f_m = stoi(fenSplit[5]);
}

