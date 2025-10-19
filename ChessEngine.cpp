
#include "Bitboard.h"

int main() {
   // const std::string starting_pos = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
   // chess_game(starting_pos);
   Bitboard bit1(1);
   bit1.set_bt1(4);
   bit1.write();
}