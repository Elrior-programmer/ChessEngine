#include "chess_game.h"
#include "Fen.h"




uint64_t calculate_pawn_attack(bool side, int square) {
	if (square < 0 || square > 63) return -1;
	uint64_t attack = 0ULL;
	uint64_t piece = 0ULL;
	set_bt1(piece, square);
	// White
	if (side) {
		if ((piece >> 7) & not_a_file) attack |= (piece >> 7);
		if ((piece >> 9) & not_h_file) attack |= (piece >> 9);
	}
	// Black
	else
	{
		if ((piece << 7) & not_h_file) attack |= (piece << 7);
		if ((piece << 9) & not_a_file) attack |= (piece << 9);
	}
	return attack;
}

void precalculate_pawn_attack_table(uint64_t table[2][64]) {
	//side white - 1 , black - 0
	for (int side = 0; side < 2; side++) {
		for (int i = 0; i < 64; i++) {
			table[side][i] = calculate_pawn_attack(side, i);
		}
	}
}

uint64_t calculate_king_attack(int square) {
	if (square < 0 || square > 63) return -1;
	uint64_t attack = 0ULL;
	uint64_t piece = 0ULL;
	set_bt1(piece, square);

	// UP (from white side xd)
	attack |= (piece >> 8);
	// Down
	attack |= (piece << 8);
	// LEFT
	if ((piece >> 1) & not_h_file) attack |= (piece >> 1);
	// RIGHT
	if ((piece << 1) & not_a_file) attack |= (piece << 1);
	// Left & UP
	if ((piece >> 9) & not_h_file) attack |= (piece >> 9);
	// RIGHT & UP
	if ((piece >> 7) & not_a_file) attack |= (piece >> 7);
	// LEFT & DOWN
	if ((piece << 7) & not_h_file) attack |= (piece << 7);
	// RIGHT & DOWN
	if ((piece << 9) & not_a_file) attack |= (piece << 9);
	return attack;
}

void precalculate_king_attack_table(uint64_t table[64]) {
	for (int i = 0; i < 64; i++) {
		table[i] = calculate_king_attack(i);
	}
}

uint64_t calculate_knight_attack(int square) {
	if (square < 0 || square > 63) return -1;
	uint64_t attack = 0ULL;
	uint64_t piece = 0ULL;
	set_bt1(piece, square);
	/*
	1---2
   4  |  3
   |     |
   -- N --
   |     |
   5  |  6
	7---8
	*/
	// 1
	if ( (piece >> 17 ) & not_h_file ) attack |= (piece >> 17);
	//2
	if ((piece >> 15) & not_a_file) attack |= (piece >> 15);
	//3
	if ((piece >> 6) & not_ab_file) attack |= (piece >> 6);
	//4
	if ((piece >> 10) & not_gh_file) attack |= (piece >> 10);
	//5 
	if ((piece << 6) & not_gh_file) attack |= (piece << 6);
	//6
	if ((piece << 10) & not_ab_file) attack |= (piece << 10);
	//7
	if ((piece << 15) & not_h_file) attack |= (piece << 15);
	//8
	if ((piece << 17) & not_a_file) attack |= (piece << 17);

	return attack;
}

void precalculate_knight_attack_table(uint64_t table[64]) {
	for (int i = 0; i < 64; i++) {
		table[i] = calculate_knight_attack(i);
	}
}

uint64_t mask_bishop_attack(int square) {
	if (square < 0 || square > 63) return -1;
	uint64_t attack = 0ULL;

	int piece_rank = square / 8;
	int piece_file = square % 8;
	// going down right
	int r, f;
	for ( r = piece_rank + 1, f = piece_file + 1; r <= 6 && f <= 6; r++, f++)
	{
		attack |= (1ULL << (r * 8 + f));
	}
	// down left
	for (r = piece_rank + 1, f = piece_file - 1; r <= 6 && f >= 1; r++, f--)
	{
		attack |= (1ULL << (r * 8 + f));
	}
	// up right
	for (r = piece_rank - 1, f = piece_file + 1; r >= 1 && f <= 6; r--, f++)
	{
		attack |= (1ULL << (r * 8 + f));
	}
	// up left
	for (r = piece_rank - 1, f = piece_file - 1; r >= 1 && f >= 1; r--, f--)
	{
		attack |= (1ULL << (r * 8 + f));
	}
	return attack;
}

uint64_t mask_rook_attack(int square) {
	if (square < 0 || square > 63) return -1;
	uint64_t attack = 0ULL;

	// going down right
	// ranks up
	for (int r = square / 8 - 1; r >= 1; r--) attack |= (1ULL << (r * 8 + square % 8));
	// ranks down
	for (int r = square / 8 + 1; r <= 6; r++) attack |= (1ULL << (r * 8 + square % 8));
	// files left
	for (int f = square % 8 - 1; f >= 1; f--) attack |= (1ULL << ((square / 8) * 8 + f));
	// files right
	for (int f = square % 8 + 1; f <= 6; f++) attack |= (1ULL << ((square / 8) * 8 + f));

	write_bitboard(attack);
	return attack;
}

void chess_game(std::string FEN) {
	uint64_t white_king = 0ULL;
	uint64_t white_queen = 0ULL;
	uint64_t white_pawn = 0ULL;
	uint64_t white_rook = 0ULL;
	uint64_t white_bishop = 0ULL;
	uint64_t white_knight = 0ULL;

	uint64_t black_king = 0ULL;
	uint64_t black_queen = 0ULL;
	uint64_t black_pawn = 0ULL;
	uint64_t black_rook = 0ULL;
	uint64_t black_bishop = 0ULL;
	uint64_t black_knight = 0ULL;

	bool turn = true; // white - true | false - black
	// castling rights
	bool white_short_castle = true;
	bool white_long_castle = true;
	bool black_short_castle = true;
	bool black_long_castle = true;
	// en passant square | you can do en passant only in 2 rows 3a-h and 6a-h+
	uint16_t en_passant = 0;

	int half_move_clock = 0;
	int full_move_number = 0;

	// Pre calculated atack table
	// Pawns [ Side (0 - black, 1 - white) ] [ square ] 
	uint64_t pawn_attack_table[2][64];
	// Kings (doesnt matter which side it is)
	uint64_t king_attack_table[64];
	// Knight
	uint64_t knight_attack_table[64];



	read_FEN(FEN, &white_king, &white_queen, &white_pawn, &white_rook, &white_bishop, &white_knight,
		&black_king, &black_queen, &black_pawn, &black_rook, &black_bishop, &black_knight,
		&turn, &white_short_castle, &white_long_castle, &black_short_castle, &black_long_castle,
		&en_passant, &half_move_clock, &full_move_number);
	;
	//precalculate_pawn_attack_table(pawn_attack_table); - turn it later on!

	//precalculate_king_attack_table(king_attack_table); - turn it later on!
	
	// precalculate_knight_attack_table(knight_attack_table); - turn it later on!

	uint64_t temp = mask_rook_attack(a4);

	
	/*write_board(&white_king, &white_queen, &white_pawn, &white_rook, &white_bishop, &white_knight,
	&black_king, &black_queen, &black_pawn, &black_rook, &black_bishop, &black_knight);*/
	
}