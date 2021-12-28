//author: GIACOMO CALABRIA

#ifndef REPLAY_PLAYER_H
#define REPLAY_PLAYER_H

#include "board.h"
#include "position.h"
#include "piece.h"
#include <string>

class replay_player{
    public:
        replay_player(board* _b, int _player_number) : b{_b}, player_number{_player_number}{};
        void turn(std::string& mossa);
    
    private:
        board* b;
        int player_number;
};

#endif