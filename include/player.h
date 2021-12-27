#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include "position.h"
#include "piece.h"

class player{

    public:
        player(board* _b, int _player_number) : b{_b}, player_number{_player_number}{};
        int get_player_number(){return player_number;}
        virtual void turn() = 0;

    protected:
        board* b;
        int player_number;
        virtual bool move() = 0;
};

#endif