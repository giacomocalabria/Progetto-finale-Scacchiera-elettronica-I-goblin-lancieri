// Author: NICOLA MARITAN

/*

*/

#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "player.h"

class computer_player : public player
{
    public:
        computer_player(board* _b, int _player_number) : player(_b, _player_number){};
        void turn() override;
    protected:
        bool move() override;
};



#endif