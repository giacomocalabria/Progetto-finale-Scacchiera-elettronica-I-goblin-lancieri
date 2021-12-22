#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class rook : public piece
{
    public:
        rook(const position& _pos, int _player) : piece(_pos, _player){}
        void move(const position& to) override;
        bool can_move_to(const position& pos) override;

    protected:
        std::vector<position> get_possible_positions() override;
};

#endif