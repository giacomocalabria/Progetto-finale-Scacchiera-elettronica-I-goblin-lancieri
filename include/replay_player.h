//author: GIACOMO CALABRIA

#ifndef REPLAY_PLAYER_H
#define REPLAY_PLAYER_H

#include <fstream>
#include <string>

#include "board.h"

class replay_player{
    public:
        replay_player(board* _b) : b{_b}{};
        void turn(std::string& mossa);
    
    private:
        board* b;
};

#endif // REPLAY_PLAYER_H