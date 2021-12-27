#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include "position.h"

class player{

    public:
        player(board* _b, int _player_number) 
            : b{_b}, player_number{_player_number}{}

        virtual void move() = 0;
        int get_player_number{return player_number;}

    protected:
        board* b;
        int player_number;
};

#endif