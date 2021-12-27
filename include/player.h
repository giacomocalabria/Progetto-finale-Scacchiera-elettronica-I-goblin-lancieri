#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

class player{
    board* b;
    
    public:
        virtual void move() = 0;
};

#endif