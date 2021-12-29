//author: GIACOMO CALABRIA

#ifndef REPLAY_PLAYER_H
#define REPLAY_PLAYER_H

#include "board.h"
#include "position.h"
#include "piece.h"
#include <string>
#include <fstream>

class replay_player{
    public:
        replay_player(board* _b, int _player_number) : b{_b}, player_number{_player_number}{};
        void turn(std::ifstream& elenco_mosse);
        int get_player_number(){return player_number;}
    
    private:
        board* b;
        int player_number;
        bool move(std::string& mossa);
};

#endif