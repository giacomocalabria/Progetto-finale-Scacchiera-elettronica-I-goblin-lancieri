//author: GIACOMO CALABRIA

#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include <iostream>

#include "player.h"

class human_player : public player{
    public:
        human_player(board* _b, player_id _id)
            :player(_b, _id) 
        {
            //std::cout << "human_player_constructor; my id: " << id << std::endl;
        }
        void turn() override;
    
    private:
        bool move() override;  
};

#endif // HUMAN_PLAYER_H