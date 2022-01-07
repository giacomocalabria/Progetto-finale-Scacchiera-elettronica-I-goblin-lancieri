//author: GIACOMO CALABRIA

#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "player.h"

class human_player : public player{
    public:
        human_player(board* _b, player_id _id)
            :player(_b, id) {}
        void turn() override;
    
    private:
        bool move() override;  
};

#endif