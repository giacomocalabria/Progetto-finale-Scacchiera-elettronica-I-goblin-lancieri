//author: GIACOMO CALABRIA

#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "player.h"

class human_player : public player{
    public:
        void turn() override;
        human_player(board* _b, int _player_number)
            :player(_b, _player_number) {}
    private:
        bool is_valid_range_position(position& _pos);
        bool move() override;   
};

#endif