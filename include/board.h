// Author: NICOLA MARITAN

#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include <vector>

class board
{
    public:
        board();
        void to_empty();    // rende la board priva di pezzi
        void move_piece(const position& from, const position& to);
        void init_game();
        static const uint8_t board_size {8};
    
    private:
        piece* board_matrix[board_size][board_size];
        std::vector<piece> white;
        std::vector<piece> black;
};

#endif