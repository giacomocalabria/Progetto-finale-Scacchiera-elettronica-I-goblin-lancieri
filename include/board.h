// Author: NICOLA MARITAN

#ifndef BOARD_H
#define BOARD_H

#include "piece.h"

class board
{
    public:
        board();
        void to_empty();
        void move_piece(const position& from, const position& to);
        static const uint8_t board_size {8};
    
    private:
        piece* board_matrix[board_size][board_size];    
};

#endif