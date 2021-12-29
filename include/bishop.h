//Autore: EDDIE CARRARO

#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class bishop : public piece
{   
    public:
        bishop(const position& _pos, int _player) : piece(_pos, _player){}
        bool can_move_to(const position& dest, const std::vector<piece*>& board_pieces) override;
        bool can_capture(const position& dest, const std::vector<piece*>& board_pieces) override;
        inline char symbol() override;// -  -  -  - > giocatore 1 o 2
        std::vector<position> get_possible_positions() override;
};

#endif