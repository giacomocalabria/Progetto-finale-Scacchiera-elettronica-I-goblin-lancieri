#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class queen : public piece
{
    public:
        queen(const position& _pos, int _player) : piece(_pos, _player){}
        inline char symbol() override;
        //void move(const position& to) override;
        bool can_move_to(const position& dest, const std::vector<piece*>& board_pieces) override;
        std::vector<position> get_possible_positions() override;
};

#endif